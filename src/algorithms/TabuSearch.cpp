#include "TabuSearch.h"
#include <algorithm>
#include <limits>

TabuSearch::TabuSearch(int timeLimit)
        : timeLimit(timeLimit), strategy(1) {}

void TabuSearch::solve(AdjacencyMatrix &graph) {
    // Get the number of vertices in the graph.
    verticesNumber = graph.getSize();

    // Initialize Tabu Table with zeros.
    std::vector<std::vector<int>> tabuTable(verticesNumber, std::vector<int>(verticesNumber, 0));

    // Set the initial path to the default permutation of vertices (0, 1, 2, ...).
    std::vector<int> currentPath = getDefaultTabuPath();

    // Calculate the initial path cost.
    int currentCost = getPathCost(currentPath, graph);

    // Initialize the best cost and path as the initial solution.
    int bestCost = currentCost;
    std::vector<int> bestPath = currentPath;

    // Penalty value for the Tabu Table (determines the duration of prohibitions).
    int punishment = 10 * verticesNumber;

    // Start the algorithm timer.
    auto start = std::chrono::high_resolution_clock::now();

    // Main loop: runs until the time limit is reached.
    while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < timeLimit) {
        // Generowanie losowej ścieżki jako punktu startowego dla tej iteracji.
        currentPath = generateRandomPath();

//        std::cout << "Strategy: " << strategy << std::endl;

        // Przeszukiwanie sąsiedztwa: iteracja po wszystkich możliwych zamianach miast w ścieżce.
        for (int i = 0; i < verticesNumber - 1; ++i) {
            int bestNextCost = std::numeric_limits<int>::max(); // Najlepszy koszt sąsiedztwa.
            int bestK = -1, bestL = -1; // Indeksy wierzchołków do zamiany.

            // Dla każdej pary wierzchołków w bieżącej ścieżce.
            for (int k = 0; k < verticesNumber - 1; ++k) {
                for (int l = k + 1; l < verticesNumber; ++l) {
//                    std::cout << "Dla pary wierzcholkow k: " << k << ", l: " << l << std::endl;
                    // Zamiana dwóch wierzchołków w ścieżce.
                    std::vector<int> newPath;
                    if (strategy == 1) {
                        newPath = swapStrategy(currentPath, k, l);
                    } else if (strategy == 2) {
                        newPath = inversionMutation(currentPath, k, l);
                    } else {
                        newPath = twoOptSwap(currentPath, k, l);
                    }

                    // Obliczenie nowego kosztu ścieżki po zamianie.
                    int newCost = getPathCost(newPath, graph);

//                    std::cout << "Nowy koszt: " << newCost << std::endl;
                    // Sprawdzenie, czy nowy koszt jest lepszy i czy ruch nie jest zabroniony przez Tablicę Tabu.
                    if (newCost < bestNextCost && tabuTable[k][l] == 0) {
                        bestNextCost = newCost;
                        bestK = k;
                        bestL = l;
                    }
                }
            }

//            std::cout << "Poza przeszukiwaniem" << std::endl;
            // Wykonanie najlepszej zamiany znalezionej w sąsiedztwie.
            if (strategy == 1) {
                currentPath = swapStrategy(currentPath, bestK, bestL);
            } else if (strategy == 2) {
                currentPath = inversionMutation(currentPath, bestK, bestL);
            } else {
                currentPath = twoOptSwap(currentPath, bestK, bestL);
            }

            // Dodanie zamiany do Tablicy Tabu z wartością kary.
//            std::cout << "Adding punishment for bestK: " << bestK << ", bestL: " << bestL << std::endl;
            if (bestK != -1 && bestL != -1) {
                tabuTable[bestK][bestL] = punishment;
            }
//            std::cout << "Added punishment" << std::endl;

            // Aktualizacja najlepszego rozwiązania, jeśli znaleziono lepszy koszt.
            if (bestNextCost < bestCost) {
//                std::cout << "setting new best cost" << std::endl;
                bestCost = bestNextCost;
                bestPath = currentPath;
            }

            // Aktualizacja czasu trwania zakazów w Tablicy Tabu.
            for (auto &row: tabuTable) {
                for (auto &element: row) {
                    if (element > 0) --element; // Redukcja czasu trwania zakazów.
                }
            }
        }
    }

    // Przypisanie najlepszego rozwiązania do atrybutów klasy.
    shortestPathLength = bestCost;
    path = bestPath;
}

int TabuSearch::getPathCost(const std::vector<int> &pathInstance, const AdjacencyMatrix &graph) {
    int cost = 0;
    for (int i = 1; i < pathInstance.size(); ++i) {
        cost += graph.getEdgeWeight(pathInstance[i - 1], pathInstance[i]);
    }
    cost += graph.getEdgeWeight(pathInstance.back(), pathInstance[0]);
    return cost;
}

std::vector<int> TabuSearch::getDefaultTabuPath() {
    std::vector<int> newPath(verticesNumber);
    std::iota(newPath.begin(), newPath.end(), 0);
    return newPath;
}

std::vector<int> TabuSearch::generateRandomPath() {
    std::vector<int> randomPath = getDefaultTabuPath();
    std::shuffle(randomPath.begin() + 1, randomPath.end(), std::mt19937{std::random_device{}()});
    return randomPath;
}

std::vector<int> TabuSearch::twoOptSwap(const std::vector<int>& route, int v1, int v2) {
    std::vector<int> newRoute;

    // 1. Take route[start] to route[v1] and add them in order to newRoute
    newRoute.insert(newRoute.end(), route.begin(), route.begin() + v1 + 1);

    // 2. Take route[v1+1] to route[v2] and add them in reverse order to newRoute
    newRoute.insert(newRoute.end(), route.rbegin() + (route.size() - v2 - 1), route.rbegin() + (route.size() - v1 - 1));

    // 3. Take route[v2+1] to route[start] and add them in order to newRoute
    newRoute.insert(newRoute.end(), route.begin() + v2 + 1, route.end());

    return newRoute;
}

std::vector<int> TabuSearch::swapStrategy(const std::vector<int>& route, int index1, int index2) {
    std::vector<int> newRoute(route);
    std::swap(newRoute[index1], newRoute[index2]);
    return newRoute;
}


std::vector<int> TabuSearch::inversionMutation(const std::vector<int>& route, int startIdx, int endIdx) {
    std::vector<int> newRoute(route);
    std::reverse(newRoute.begin() + startIdx, newRoute.begin() + endIdx + 1);
    return newRoute;
}

std::string TabuSearch::toString() {
    std::string result;
    for (int city: path) {
        result += std::to_string(city) + " -> ";
    }
    result += "0";
    return result;
}

void TabuSearch::setStrategy(int s) {
    strategy = s;
}
