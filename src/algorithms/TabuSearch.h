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
    enum NeighborhoodStrategy { SWAP, REVERSE, INSERT };
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
    int calculatePathCost(const std::vector<int>& path, AdjacencyMatrix& graph) {
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
            for (const auto &candidate : candidates) {
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

    // Generate neighborhoods
    std::vector<std::vector<int>> generateNeighborhood(const std::vector<int>& path) {
        std::vector<std::vector<int>> neighborhood;

        switch (strategy) {
            case SWAP:
                for (size_t i = 0; i < path.size(); ++i) {
                    for (size_t j = i + 1; j < path.size(); ++j) {
                        std::vector<int> newPath = path;
                        std::swap(newPath[i], newPath[j]);
                        neighborhood.push_back(newPath);
                    }
                }
                break;

            case REVERSE:
                for (size_t i = 0; i < path.size(); ++i) {
                    for (size_t j = i + 1; j < path.size(); ++j) {
                        std::vector<int> newPath = path;
                        std::reverse(newPath.begin() + i, newPath.begin() + j + 1);
                        neighborhood.push_back(newPath);
                    }
                }
                break;

            case INSERT:
                for (size_t i = 0; i < path.size(); ++i) {
                    for (size_t j = 0; j < path.size(); ++j) {
                        if (i == j) continue;
                        std::vector<int> newPath = path;
                        int city = newPath[i];
                        newPath.erase(newPath.begin() + i);
                        newPath.insert(newPath.begin() + j, city);
                        neighborhood.push_back(newPath);
                    }
                }
                break;
        }

        return neighborhood;
    }

    // Check if path is tabu
    bool isTabu(const std::vector<int>& path) {
        for (const auto& tabuPath : tabuList) {
            if (tabuPath == path) {
                return true;
            }
        }
        return false;
    }

    // Add path to tabu list
    void addTabu(const std::vector<int>& path) {
        if (tabuList.size() >= maxTabuSize) {
            tabuList.erase(tabuList.begin());
        }
        tabuList.push_back(path);
    }

    void diversify(std::vector<int>& path, std::mt19937& rng) {
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

public:
    TabuSearch(int diversificationFactor, int maxTabuSize, std::chrono::seconds timeLimit, NeighborhoodStrategy strategy)
            : diversificationFactor(diversificationFactor), maxTabuSize(maxTabuSize), timeLimit(timeLimit), strategy(strategy) {}

            TabuSearch()
            : diversificationFactor(10), maxTabuSize(10), timeLimit(30), strategy(SWAP) {
    }

    void solve(AdjacencyMatrix& graph) override {
        std::cout << "calculating for graph size: " << graph.getSize() << std::endl;

        size = graph.getSize();
        tabuList.clear();
        static std::random_device rd;
        std::mt19937 gen(rd());

//        initial path creation
        Greedy greedy;
        greedy.solve(graph);
        bestPath = greedy.path;

        shortestPathLength = calculatePathCost(bestPath, graph);

        std::vector<int> currentPath = bestPath;
        int currentCost = shortestPathLength;

        int bestNeighborCost = INT_MAX;

        auto start = std::chrono::high_resolution_clock::now();
        while (true) {
            auto now = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - start) > timeLimit) {
                break;
            }

            auto neighborhood = generateNeighborhood(currentPath);
            std::vector<int> bestNeighbor;

            for (const auto& neighbor : neighborhood) {
                if (std::find(tabuList.begin(), tabuList.end(), neighbor) == tabuList.end()){
                    int neighborCost = calculatePathCost(neighbor, graph);
                    if (neighborCost < bestNeighborCost) {
                        bestNeighbor = neighbor;
                        bestNeighborCost = neighborCost;
                    }
                }
            }

            if (bestNeighbor.empty()) {
                // No non-tabu neighbors found,
                // terminate the search
//                break;
                diversify(currentPath, gen);
                continue;
//                std::cout << "would break" << std::endl;
            }

            currentPath = bestNeighbor;
            currentCost = bestNeighborCost;
            tabuList.push_back(bestNeighbor);

            if (tabuList.size() > 20) {
                // Remove the oldest entry from the
                // tabu list if it exceeds the size
                tabuList.erase(tabuList.begin());
            }

            if (bestNeighborCost < shortestPathLength) {
                std::cout<< " new best solution found with len: " << bestNeighborCost << std::endl;
                bestPath = bestNeighbor;
                shortestPathLength = bestNeighborCost;

                bestNeighborCost = INT_MAX;
            }
        }
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
        for (int node : bestPath) {
            oss << node << " -> ";
        }
        oss << bestPath[0]; // Close the cycle
        return oss.str();
    }
};


#endif // PEA_TABUSEARCH_H
