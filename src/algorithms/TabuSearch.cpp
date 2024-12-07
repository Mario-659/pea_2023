#include "TabuSearch.h"
#include <algorithm>
#include <limits>

TabuSearch::TabuSearch(int timeLimit)
        : timeLimit(timeLimit) {}

void TabuSearch::solve(AdjacencyMatrix& graph) {
    verticesNumber = graph.getSize();

    std::vector<std::vector<int>> tabuTable(verticesNumber, std::vector<int>(verticesNumber, 0));
    std::vector<int> currentPath = getDefaultTabuPath();
    int currentCost = getPathCost(currentPath, graph);
    int bestCost = currentCost;
    std::vector<int> bestPath = currentPath;
    int punishment = 10 * verticesNumber;

    auto start = std::chrono::high_resolution_clock::now();

    while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < timeLimit) {
        currentPath = generateRandomPath();

        // Neighborhood search with Tabu Table restrictions
        for (int i = 0; i < verticesNumber - 1; ++i) {
            int bestNextCost = std::numeric_limits<int>::max();
            int bestK = -1, bestL = -1;

            for (int k = 0; k < verticesNumber - 1; ++k) {
                for (int l = k + 1; l < verticesNumber; ++l) {
                    std::swap(currentPath[k], currentPath[l]);
                    int newCost = getPathCost(currentPath, graph);
                    if (newCost < bestNextCost && tabuTable[k][l] == 0) {
                        bestNextCost = newCost;
                        bestK = k;
                        bestL = l;
                    }
                    std::swap(currentPath[k], currentPath[l]);
                }
            }

            std::swap(currentPath[bestK], currentPath[bestL]);
            tabuTable[bestK][bestL] = punishment;

            if (bestK != -1 && bestL != -1) {
                std::swap(currentPath[bestK], currentPath[bestL]);
                tabuTable[bestK][bestL] = verticesNumber;

                if (bestNextCost < bestCost) {
                    bestCost = bestNextCost;
                    bestPath = currentPath;
                }
            }

            // Update Tabu Table durations
            for (auto& row : tabuTable) {
                for (auto& element : row) {
                    if (element > 0) --element;
                }
            }
        }
    }
    shortestPathLength = bestCost;
    path = bestPath;
}

int TabuSearch::getPathCost(const std::vector<int>& pathInstance, const AdjacencyMatrix& graph) {
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
    std::shuffle(randomPath.begin(), randomPath.end(), std::mt19937{std::random_device{}()});
    return randomPath;
}

std::string TabuSearch::toString() {
    std::string result;
    for (int city : path) {
        result += std::to_string(city) + " -> ";
    }
    result += "0";
    return result;
}
