#include "TabuSearch.h"
#include <algorithm>
#include <limits>

TabuSearch::TabuSearch(int timeLimit)
        : timeLimit(timeLimit), strategy(1) {}

void TabuSearch::solve(AdjacencyMatrix& graph) {
    verticesNumber = graph.getSize();

    std::vector<std::vector<int>> tabuTable(verticesNumber, std::vector<int>(verticesNumber, 0));
    std::vector<int> currentPath = getDefaultTabuPath();
    int currentCost = getPathCost(currentPath, graph);
    int bestCost = currentCost;
    std::vector<int> bestPath = currentPath;

    auto start = std::chrono::high_resolution_clock::now();

    while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < timeLimit) {
        currentPath = generateRandomPath();

        // Neighborhood search with Tabu Table restrictions
        for (int i = 0; i < verticesNumber - 1; ++i) {
            int bestNextCost = std::numeric_limits<int>::max();
            std::vector<int> bestNextPath;
            int bestK = -1, bestL = -1;

            for (int k = 0; k < verticesNumber - 1; ++k) {
                for (int l = k + 1; l < verticesNumber; ++l) {
                    std::vector<int> newPath = getNeighbor(currentPath, k, l);
                    int newCost = getPathCost(newPath, graph);
                    if (newCost < bestNextCost && tabuTable[k][l] == 0) {
                        bestNextPath = newPath;
                        bestNextCost = newCost;
                        bestK = k;
                        bestL = l;
                    }
                }
            }

            if (bestK != -1 && bestL != -1) {
                tabuTable[bestK][bestL] = verticesNumber;

                if (bestNextCost < bestCost) {
                    bestCost = bestNextCost;
                    bestPath = bestNextPath;
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
std::vector<int> TabuSearch::getNeighbor(const std::vector<int>& route, int v1, int v2) {
    if (strategy == 1) {
        return swapStrategy(route, v1, v2);
    } else if (strategy == 2) {
        return inversionMutation(route, v1, v2);
    } else return twoOptSwap(route, v1, v2);
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
    for (int city : path) {
        result += std::to_string(city) + " -> ";
    }
    result += std::to_string(path[0]);
    return result;
}

void TabuSearch::setStrategy(int s) {
    strategy = s;
}
