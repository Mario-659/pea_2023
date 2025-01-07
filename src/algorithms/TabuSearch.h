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

#define TABU_STEPS 20
#define INTENSIFICATION_FACTOR 4

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

    std::vector<int> generateSemiRandomSolution(AdjacencyMatrix& graph) {
        std::vector<int> route;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> vertexDist(0, graph.getSize() - 1);

        int randomCount = std::uniform_int_distribution<>(1, graph.getSize())(gen);

        // Random part
        while (route.size() < static_cast<size_t>(randomCount)) {
            int candidate = vertexDist(gen);
            if (std::find(route.begin(), route.end(), candidate) == route.end()) {
                route.push_back(candidate);
            }
        }

        // Greedy part
        while (route.size() < static_cast<size_t>(graph.getSize())) {
            int lastVertex = route.back();
            int nextVertex = -1;
            int minEdge = INT_MAX;

            for (int j = 0; j < graph.getSize(); ++j) {
                if (std::find(route.begin(), route.end(), j) == route.end() && graph.getEdgeWeight(lastVertex, j) < minEdge) {
                    minEdge = graph.getEdgeWeight(lastVertex, j);
                    nextVertex = j;
                }
            }
            route.push_back(nextVertex);
        }
        return route;
    }

public:
    TabuSearch(std::chrono::seconds timeLimit, NeighborhoodStrategy strategy)
            : timeLimit(timeLimit),
              strategy(strategy) {}

    TabuSearch()
            : timeLimit(30), strategy(SWAP) {
    }

    // Solve method implementing the Tabu Search algorithm
    void solve(AdjacencyMatrix& graph) override {
        std::vector<int> currentRoute;
        Greedy greedy;
        greedy.solve(graph);
        currentRoute = greedy.path; // Start with a greedy solution

        int optimalRouteLength = calculatePathCost(currentRoute, graph);
        std::vector<int> optimalRoute = currentRoute;

        int tabuSteps = TABU_STEPS; // Initial tabu tenure
        int stopCounter = 0;
        int iterationsToRestart = graph.getSize(); // Number of iterations before diversification
        std::vector<std::vector<int>> tabuList; // Tabu list to store prohibited moves, each element consists of {tabu_steps, vertex_index_1, vertex_index_2}

        auto start = std::chrono::high_resolution_clock::now();

        while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start) < timeLimit) {
            bool improvementFound = false;
            std::vector<int> nextRoute;
            int nextRouteLength = INT_MAX;
            std::vector<int> bestTabuMove(3, 0);

            // Explore neighborhood, find best neighbour
            for (int i = 1; i < graph.getSize() - 1; ++i) {
                for (int j = i + 1; j < graph.getSize(); ++j) {
                    std::vector<int> neighborRoute = currentRoute;

                    // Apply the chosen neighborhood strategy
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

                    // Check if the move is tabu
                    bool isTabu = std::any_of(tabuList.begin(), tabuList.end(), [&](const std::vector<int>& tabu) {
                        return (tabu[1] == i && tabu[2] == j) || (tabu[1] == j && tabu[2] == i);
                    });

                    // Apply aspiration criteria: allow tabu moves if they improve the optimal solution
                    if (isTabu && neighborCost >= optimalRouteLength) continue;

                    // Update the best move if the current neighbor is better
                    if (neighborCost < nextRouteLength) {
                        nextRouteLength = neighborCost;
                        nextRoute = neighborRoute;
                        bestTabuMove = {tabuSteps, i, j};
                    }
                }
            }

            // Move to the best neighbor
            currentRoute = nextRoute;

            // Update the optimal solution if an improvement is found
            if (nextRouteLength < optimalRouteLength) {
                optimalRouteLength = nextRouteLength;
                optimalRoute = nextRoute;
                stopCounter = 0;
                improvementFound = true;
            } else {
                // increment diversification counter
                ++stopCounter;
            }

            // Update tabu list: decrement tenure and remove expired moves
            for (size_t i = 0; i < tabuList.size(); ) {
                if (--tabuList[i][0] == 0) {
                    tabuList[i] = tabuList.back(); // Replace with the last element
                    tabuList.pop_back(); // Remove the last element
                } else {
                    ++i; // Increment only if no element was removed
                }
            }

            tabuList.push_back(bestTabuMove); // Add the best move to the tabu list

            // Perform diversification if no improvement for a given number of iterations
            if (stopCounter >= iterationsToRestart) {
                currentRoute = generateSemiRandomSolution(graph);
                stopCounter = 0;
            }

            // Adjust tabu tenure: intensify search if improvement is found
            if (improvementFound) {
                tabuSteps /= INTENSIFICATION_FACTOR;
            } else {
                tabuSteps = TABU_STEPS;
            }
        }

        bestPath = optimalRoute; // Store the best path found
        shortestPathLength = optimalRouteLength; // Store its length
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
