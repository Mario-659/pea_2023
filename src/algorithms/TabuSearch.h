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
    std::vector<int> bestPath;
private:
    NeighborhoodStrategy strategy;
    std::chrono::seconds timeLimit;

    int calculatePathCost(const std::vector<int> &path, AdjacencyMatrix &graph) {
        int cost = 0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            cost += graph.getEdgeWeight(path[i], path[i + 1]);
        }
        cost += graph.getEdgeWeight(path.back(), path.front());
        return cost;
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

                for (int j : route) {
                    if (j == randomVertex) {
                        vertexUsed = true;
                        break;
                    }
                }
            } while (vertexUsed);

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
                for (int k : route) {
                    if (j == k) {
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

//        route.push_back(route.front());
        return route;
    }

public:
    TabuSearch(std::chrono::seconds timeLimit, NeighborhoodStrategy strategy)
            : timeLimit(timeLimit),
              strategy(strategy) {}

    TabuSearch()
            : timeLimit(30), strategy(SWAP) {
    }

    void solve(AdjacencyMatrix& graph) override {
        std::vector<int> currentRoute;
        Greedy greedy;
        greedy.solve(graph);
        currentRoute = greedy.path;

        int optimalRouteLength = calculatePathCost(currentRoute, graph);
        std::vector<int> optimalRoute = currentRoute;

        int tabuSteps = 20;
        int stopCounter = 0;
        int iterationsToRestart = graph.getSize();
        std::vector<std::vector<int>> tabuList;

        auto start = std::chrono::high_resolution_clock::now();

        while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start) < timeLimit) {

            bool improvementFound = false;
            std::vector<int> nextRoute;
            int nextRouteLength = INT_MAX;
            std::vector<int> bestTabuMove(3, 0);

            for (int i = 1; i < graph.getSize() - 1; ++i) {
                for (int j = i + 1; j < graph.getSize(); ++j) {

                    std::vector<int> neighborRoute = currentRoute;

                    switch (strategy) {
                        case SWAP:
                            std::swap(neighborRoute[i], neighborRoute[j]);
                            break;
                        case REVERSE:
                            std::reverse(neighborRoute.begin() + i, neighborRoute.begin() + j + 1);
                            break;
                        case INSERT:
                            int element = neighborRoute[j];
                            neighborRoute.erase(neighborRoute.begin() + j);
                            neighborRoute.insert(neighborRoute.begin() + i, element);
                            break;
                    }

                    int neighborCost = calculatePathCost(neighborRoute, graph);

                    bool isTabu = std::any_of(tabuList.begin(), tabuList.end(), [&](const std::vector<int>& tabu) {
                        return (tabu[1] == i && tabu[2] == j) || (tabu[1] == j && tabu[2] == i);
                    });

                    if (isTabu && neighborCost >= optimalRouteLength) continue;

                    if (neighborCost < nextRouteLength) {
                        nextRouteLength = neighborCost;
                        nextRoute = neighborRoute;
                        bestTabuMove = {tabuSteps, i, j};
                    }
                }
            }

            currentRoute = nextRoute;
            if (nextRouteLength < optimalRouteLength) {
                optimalRouteLength = nextRouteLength;
                optimalRoute = nextRoute;
                stopCounter = 0;
                improvementFound = true;
            } else {
                ++stopCounter;
            }

            for (size_t i = 0; i < tabuList.size(); ) {
                if (--tabuList[i][0] == 0) {
                    tabuList[i] = tabuList.back(); // Replace current element with the last one
                    tabuList.pop_back();           // Remove the last element
                } else {
                    ++i; // Only increment the index if no element was removed
                }
            }


            tabuList.push_back(bestTabuMove);

            if (stopCounter >= iterationsToRestart) {
                currentRoute = generateSemiRandomSolution(graph);
                stopCounter = 0;
            }

            if (improvementFound) {
                tabuSteps /= 4;
            } else {
                tabuSteps = 20;
            }
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
