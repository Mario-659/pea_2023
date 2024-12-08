#include "TabuSearch.h"
#include <algorithm>
#include <limits>

TabuSearch::TabuSearch(int timeLimit)
        : timeLimit(timeLimit) {}

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
        // Generate a random path as the starting point for this iteration.
        currentPath = generateRandomPath();

        // Neighborhood search: iterate over all possible 2-opt swaps.
        int bestNextCost = std::numeric_limits<int>::max(); // Best cost in the neighborhood.
        std::vector<int> bestNeighbor; // Store the best neighbor path.

        for (int k = 0; k < verticesNumber - 1; ++k) {
            for (int l = k + 1; l < verticesNumber; ++l) {
                // Perform the 2-opt swap.
                std::vector<int> newPath = twoOptSwap(currentPath, k, l);

                // Calculate the new path cost.
                int newCost = getPathCost(newPath, graph);

                // Check if the new cost is better and if the move is not forbidden by the Tabu Table.
                if (newCost < bestNextCost && tabuTable[k][l] == 0) {
                    bestNextCost = newCost;
                    bestNeighbor = newPath;
                }
            }
        }

        // Update the current path to the best neighbor found in the neighborhood.
        currentPath = bestNeighbor;

        // Add the move to the Tabu Table with the penalty value.
        if (!bestNeighbor.empty()) {
            for (int i = 0; i < verticesNumber - 1; ++i) {
                for (int j = i + 1; j < verticesNumber; ++j) {
                    if (currentPath[i] != bestNeighbor[i] || currentPath[j] != bestNeighbor[j]) {
                        tabuTable[i][j] = punishment;
                    }
                }
            }
        }

        // Update the best solution if a better cost is found.
        if (bestNextCost < bestCost) {
            bestCost = bestNextCost;
            bestPath = currentPath;
        }

        // Reduce the duration of prohibitions in the Tabu Table.
        for (auto &row : tabuTable) {
            for (auto &element : row) {
                if (element > 0) --element;
            }
        }
    }

    // Assign the best solution to class attributes.
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
    std::shuffle(randomPath.begin(), randomPath.end(), std::mt19937{std::random_device{}()});
    return randomPath;
}

//procedure 2optSwap(route, v1, v2) {
//1. take route[start] to route[v1] and add them in order to new_route
//2. take route[v1+1] to route[v2] and add them in reverse order to new_route
//3. take route[v2+1] to route[start] and add them in order to new_route
//return new_route;
//}
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



std::string TabuSearch::toString() {
    std::string result;
    for (int city: path) {
        result += std::to_string(city) + " -> ";
    }
    result += "0";
    return result;
}
