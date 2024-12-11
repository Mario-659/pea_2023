#ifndef PEA_TABUSEARCH_H
#define PEA_TABUSEARCH_H

#include "TSPSolver.h"
#include "../graphs/AdjacencyMatrix.h"
#include "Greedy.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>

#include <vector>
#include <queue>
#include <unordered_set>
#include <random>
#include <chrono>
#include <climits>
#include <algorithm>
#include <sstream>
#include <iostream>

class TabuSearch : public TSPSolver {
public:
    enum NeighborhoodStrategy {
        SWAP, REVERSE, INSERT
    };
private:
    std::vector<int> bestPath;
    int diversificationFactor; // Helps escape local optima
    std::chrono::seconds timeLimit;
    std::vector<std::vector<int>> tabuList;
    int maxTabuSize;

    NeighborhoodStrategy strategy;

    // Helper to generate a random number in range [low, high]
    int randomInt(int low, int high) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(low, high);
        return dis(gen);
    }

    // Helper to calculate the cost of a given path, assumes path is already closed
    int calculatePathCost(const std::vector<int> &path, AdjacencyMatrix &graph) {
        int cost = 0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
//            std::cout << "adding cost " << graph.getEdgeWeight(path[i], path[i + 1]) << std::endl;
            cost += graph.getEdgeWeight(path[i], path[i + 1]);
        }
//        std::cout << "adding return cost " << path.back() << "---helo---" << path.front() << std::endl;
        cost += graph.getEdgeWeight(path.back(), path.front());
        return cost;
    }

    // Generate initial path with GENERAL RANDOMIZED ADAPTIVE SEARCH PROCESS
    std::vector<int> constructSolution(AdjacencyMatrix &graph, double alpha, std::mt19937 &gen) {
        int verticesNumber = graph.getSize();
        std::vector<bool> visited(verticesNumber, false);
        std::vector<int> path;
        int currentVertex = 0;  // Start from the first vertex
        path.push_back(currentVertex);
        visited[currentVertex] = true;

        while (path.size() < verticesNumber) {
            // Create a list of candidate neighbors with their weights
            std::vector<std::pair<int, int>> candidates; // (neighbor, weight)
            for (int i = 0; i < verticesNumber; ++i) {
                if (!visited[i]) {
                    candidates.emplace_back(i, graph.getEdgeWeight(currentVertex, i));
                }
            }

            // Sort candidates by weight
            std::sort(candidates.begin(), candidates.end(), [](const auto &a, const auto &b) {
                return a.second < b.second;
            });

            // Determine the threshold for the RCL
            int minWeight = candidates.front().second;
            int maxWeight = candidates.back().second;
            int threshold = minWeight + alpha * (maxWeight - minWeight);

            // Build the restricted candidate list (RCL)
            std::vector<int> rcl;
            for (const auto &candidate: candidates) {
                if (candidate.second <= threshold) {
                    rcl.push_back(candidate.first);
                }
            }

            // Select a random candidate from the RCL
            std::uniform_int_distribution<int> dist(0, rcl.size() - 1);
            int selected = rcl[dist(gen)];

            // Add the selected vertex to the path and mark it as visited
            path.push_back(selected);
            visited[selected] = true;
            currentVertex = selected;
        }

        // Return to the starting vertex to complete the cycle
        path.push_back(path.front());
        return path;
    }

    // Generate neighbor
    std::vector<int> getNeighbor(const std::vector<int> &path, int v1, int v2) {
        std::vector<int> neighbor(path);

        switch (strategy) {
            case SWAP:
                std::swap(neighbor[v1], neighbor[v2]);
                break;

            case REVERSE:
                std::reverse(neighbor.begin() + v1, neighbor.begin() + v2 + 1);
                break;

            case INSERT:
                int city = neighbor[v1];
                neighbor.erase(neighbor.begin() + v1);
                neighbor.insert(neighbor.begin() + v2, city);
                break;
        }

        return neighbor;
    }

    // Check if path is tabu
    bool isTabu(const std::vector<int> &path) {
        for (const auto &tabuPath: tabuList) {
            if (tabuPath == path) {
                return true;
            }
        }
        return false;
    }

    // Add path to tabu list
    void addTabu(const std::vector<int> &path) {
        if (tabuList.size() >= maxTabuSize) {
            tabuList.erase(tabuList.begin());
        }
        tabuList.push_back(path);
    }

    void diversify(std::vector<int> &path, std::mt19937 &rng) {
        std::uniform_int_distribution<size_t> dist(0, path.size() - 1);
        size_t start = dist(rng);
        size_t end = dist(rng);
//        std::cout << "start: " << start << ", end: " << end << std::endl;
        if (start > end) {
            std::swap(start, end);
        }
//        std::cout << "start: " << start << ", end: " << end << std::endl;

        std::shuffle(path.begin() + start, path.begin() + end + 1, rng);
    }

    std::vector<int> generateSemiRandomSolution(AdjacencyMatrix &graph) {
        // ALGORYTM hybrydowy losowo-zachlanny
        // Losowa czesc wierzcholkow jest losowana, reszta zachlannie
        // Implementacja: Jan Potocki 2019
        std::vector<int> route;

        std::random_device randomSrc;
        std::default_random_engine randomGen(randomSrc());
        std::uniform_int_distribution<> vertexNumberDist(1, graph.getSize());
        std::uniform_int_distribution<> vertexDist(0, graph.getSize() - 1);

        // Liczba losowanych wierzcholkow
        unsigned randomVertexNumber = vertexNumberDist(randomGen);

        // Czesc losowa
        for (int i = 0; i < randomVertexNumber; i++) {
            unsigned randomVertex;
            bool vertexUsed;

            do {
                randomVertex = vertexDist(randomGen);
                vertexUsed = false;

                for (int j = 0; j < route.size(); j++) {
                    if (route.at(j) == randomVertex) {
                        vertexUsed = true;
                        break;
                    }
                }
            } while (vertexUsed == true);

            route.push_back(randomVertex);
        }

        // Czesc zachlanna
        for (int i = 0; i < graph.getSize() - randomVertexNumber; i++) {
            int minEdge = -1;
            unsigned nextVertex;
            for (int j = 0; j < graph.getSize(); j++) {
                // Odrzucenie samego siebie lub wierzcholka startowego
                // (zeby bylo szybciej)
                if (route.back() == j || route.front() == j)
                    continue;

                // Odrzucenie krawedzi do wierzcholka umieszczonego juz na trasie
                bool vertexUsed = false;
                for (int k = 0; k < route.size(); k++) {
                    if (j == route.at(k)) {
                        vertexUsed = true;
                        break;
                    }
                }
                if (vertexUsed)
                    continue;

                // Znalezienie najkrotszej mozliwej jeszcze do uzycia krawedzi
                unsigned consideredLength = graph.getEdgeWeight(route.back(), j);

                // PEA 2 Plus
                // Jan Potocki 2019
                if (minEdge == -1) {
                    minEdge = consideredLength;
                    nextVertex = j;
                } else if (minEdge > consideredLength) {
                    minEdge = consideredLength;
                    nextVertex = j;
                }
            }
            route.push_back(nextVertex);
        }

        route.push_back(route.front());
        return route;
    }

public:
    TabuSearch(int diversificationFactor, int maxTabuSize, std::chrono::seconds timeLimit,
               NeighborhoodStrategy strategy)
            : diversificationFactor(diversificationFactor), maxTabuSize(maxTabuSize), timeLimit(timeLimit),
              strategy(strategy) {}

    TabuSearch()
            : diversificationFactor(10), maxTabuSize(10), timeLimit(30), strategy(SWAP) {
    }

    void solve(AdjacencyMatrix &graph) override {
        // ALGORYTM oparty na metaheurystyce tabu search z dywersyfikacja i sasiedztwem typu swap
        // Rdzen przeznaczony do uruchamiania jako jeden watek
        // (refactoring 2019)

        std::vector<int> optimalRoute;     // Tu bedziemy zapisywac optymalne (w danej chwili) rozwiazanie
        int optimalRouteLength = -1;            // -1 - bedziemy odtad uznawac, ze to jest nieskonczonosc ;-)
        std::vector<int> currentRoute;     // Rozpatrywane rozwiazanie

        // Wyznaczenie poczatkowego rozwiazania algorytmem zachlannym
        Greedy greedy;
        greedy.solve(graph);
        currentRoute = greedy.path;

        int tabuSteps = 20;

        // Inicjalizacja glownej petli...
        std::vector<std::vector<unsigned> > tabuArray;
        unsigned currentTabuSteps = tabuSteps;
        int stopCounter = 0;

        int iterationsToRestart = size;
        // Rdzen algorytmu

        auto start = std::chrono::high_resolution_clock::now();
        while (true) {
            auto now = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - start) > timeLimit) {
                break;
            }

            bool cheeseSupplied = true;
            bool intensification = false;

            while (cheeseSupplied) {
                std::vector<int> nextRoute;
                int nextRouteLength = -1;

                std::vector<unsigned> nextTabu(3, 0);
                nextTabu.at(0) = currentTabuSteps;

                // Generowanie sasiedztwa typu swap przez zamiane wierzcholkow
                // (wierzcholka startowego i zarazem ostatniego nie ruszamy,
                // pomijamy tez od razu aktualny wierzcholek)
                for (int i = 1; i < graph.getSize() - 1; i++) {
                    for (int j = i + 1; j < graph.getSize(); j++) {
                        std::vector<int> neighbourRoute = currentRoute;
//                        std::cout << "Current route cost: " << calculatePathCost(neighbourRoute, graph) << std::endl;
                        // Zamiana
                        switch (strategy) {
                            case SWAP:
                            {
                                unsigned buffer = neighbourRoute.at(j);
                                neighbourRoute.at(j) = neighbourRoute.at(i);
                                neighbourRoute.at(i) = buffer;
                            }
                                break;

                            case REVERSE:
                            {
                                std::reverse(neighbourRoute.begin() + i, neighbourRoute.begin() + j + 1);
                            }
                                break;

                            case INSERT:
                            {
                                unsigned element = neighbourRoute.at(j);
                                neighbourRoute.erase(neighbourRoute.begin() + j);
                                neighbourRoute.insert(neighbourRoute.begin() + i, element);
                            }
                                break;
                        }

//                        std::cout << "Neighbor route cost: " << calculatePathCost(neighbourRoute, graph) << std::endl;
                        unsigned neighbourRouteLength = 0;
                        for (int i = 1; i < neighbourRoute.size(); i++)
                            neighbourRouteLength += graph.getEdgeWeight(neighbourRoute.at(i - 1),
                                                                        neighbourRoute.at(i));

                        // Sprawdzenie, czy dany ruch nie jest na liscie tabu
                        // (dwa wierzcholki)
                        bool tabu = false;
                        for (int k = 0; k < tabuArray.size(); k++) {
                            if (tabuArray.at(k).at(1) == i && tabuArray.at(k).at(2) == j) {
                                tabu = true;
                                break;
                            }

                            if (tabuArray.at(k).at(1) == j && tabuArray.at(k).at(2) == i) {
                                tabu = true;
                                break;
                            }
                        }

                        // Kryterium aspiracji...
                        if (tabu && neighbourRouteLength >= optimalRouteLength)
                            // ...jezeli niespelnione - pomijamy ruch
                            continue;

                        if (nextRouteLength == -1) {
                            nextRouteLength = neighbourRouteLength;
                            nextRoute = neighbourRoute;
                            nextTabu.at(1) = i;
                            nextTabu.at(2) = j;
                        } else if (nextRouteLength > neighbourRouteLength) {
                            nextRouteLength = neighbourRouteLength;
                            nextRoute = neighbourRoute;
                            nextTabu.at(1) = i;
                            nextTabu.at(2) = j;
                        }
                    }
                }

                currentRoute = nextRoute;

                if (optimalRouteLength == -1) {
                    optimalRouteLength = nextRouteLength;
                    optimalRoute = nextRoute;

                    // Reset licznika
                    stopCounter = 0;
                } else if (optimalRouteLength > nextRouteLength) {
                    optimalRouteLength = nextRouteLength;
                    optimalRoute = nextRoute;

                    // Zaplanowanie intensyfikacji przy znalezieniu nowego optimum
                    intensification = true;

                    // Reset licznika
                    stopCounter = 0;
                }

                // Weryfikacja listy tabu...
                int tabuPos = 0;
                while (tabuPos < tabuArray.size()) {
                    // ...aktualizacja kadencji na liscie tabu
                    tabuArray.at(tabuPos).at(0)--;

                    //...usuniecie zerowych kadencji
                    if (tabuArray.at(tabuPos).at(0) == 0)
                        tabuArray.erase(tabuArray.begin() + tabuPos);
                    else
                        tabuPos++;
                }

                // ...dopisanie ostatniego ruchu do listy tabu
                tabuArray.push_back(nextTabu);

                // Zliczenie iteracji
                stopCounter++;

                // Sprawdzenie warunku zatrzymania
                // Przy aktywowanej dywersyfikacji - po zadanej liczbie iteracji bez poprawy
                if (stopCounter >= iterationsToRestart)
                    cheeseSupplied = false;
            }

            // Intensyfikacja przeszukiwania przez skrócenie kadencji
            // (jezeli w ostatnim przebiegu znaleziono nowe minimum)
            if (intensification) {
                currentRoute = optimalRoute;
                currentTabuSteps = tabuSteps / 4;
            } else {
                // Dywersyfikacja przez wygenerowanie nowego
                // rozwiazania startowego algorytmem hybrydowym losowo-zachlannym
                currentRoute = generateSemiRandomSolution(graph);
                currentTabuSteps = tabuSteps;
            }

            // Reset licznika iteracji przed restartem
            stopCounter = 0;
        }

        bestPath = optimalRoute;
        shortestPathLength = optimalRouteLength;
    }

    void setStrategy(NeighborhoodStrategy strategy) {
        this->strategy = strategy;
    }

    void setTimeLimit(std::chrono::seconds timeLimit) {
        this->timeLimit = timeLimit;
    };

    std::string toString() override {
        std::ostringstream oss;
        oss << "Shortest Path Length: " << shortestPathLength << "\nPath: ";
        for (int node: bestPath) {
            oss << node << " -> ";
        }
        oss << bestPath[0]; // Close the cycle
        return oss.str();
    }
};


#endif // PEA_TABUSEARCH_H
