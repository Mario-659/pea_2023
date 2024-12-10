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

    // Helper to calculate the cost of a given path
    int calculatePathCost(const std::vector<int>& path, AdjacencyMatrix& graph) {
        int cost = 0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            cost += graph.getEdgeWeight(path[i], path[i + 1]);
        }
        cost += graph.getEdgeWeight(path.back(), path.front());
        return cost;
    }

    // Generate initial random path
    std::vector<int> generateInitialPath(int size) {
        std::vector<int> path(size);
        std::iota(path.begin(), path.end(), 0);
        std::shuffle(path.begin(), path.end(), std::mt19937{ std::random_device{}() });
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

    void diversify(std::vector<int> path) {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,path.size() - 2);
        int offsetBegin = dist6(rng);
        std::uniform_int_distribution<std::mt19937::result_type> distEnt(1,path.size() - 1);
        int offsetEnd = distEnt(rng) % path.size() - offsetBegin - 1;
        std::shuffle(path.begin() + offsetBegin, path.begin() + offsetEnd, std::mt19937{ std::random_device{}()});
    }

public:
    TabuSearch(int diversificationFactor, int maxTabuSize, std::chrono::seconds timeLimit, NeighborhoodStrategy strategy)
            : diversificationFactor(diversificationFactor), maxTabuSize(maxTabuSize), timeLimit(timeLimit), strategy(strategy) {}

            TabuSearch()
            : diversificationFactor(10), maxTabuSize(10), timeLimit(30), strategy(SWAP) {}

    void solve(AdjacencyMatrix& graph) override {
        auto start = std::chrono::high_resolution_clock::now();
        size = graph.getSize();
        Greedy greedy;
        greedy.solve(graph);
        bestPath = greedy.path;
//        bestPath = generateInitialPath(size);
        shortestPathLength = calculatePathCost(bestPath, graph);

        std::vector<int> currentPath = bestPath;
        int currentCost = shortestPathLength;

        while (true) {
            auto now = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - start) > timeLimit) {
                break;
            }

            auto neighborhood = generateNeighborhood(currentPath);
            std::vector<int> bestNeighbor;
            int bestNeighborCost = INT_MAX;

            for (const auto& neighbor : neighborhood) {
                if (isTabu(neighbor)) continue;

                int cost = calculatePathCost(neighbor, graph);
                if (cost < bestNeighborCost) {
                    bestNeighbor = neighbor;
//                    std::cout << "New best cost: " << cost << std::endl;
                    bestNeighborCost = cost;
                }
            }

            if (!bestNeighbor.empty()) {
                currentPath = bestNeighbor;
                currentCost = bestNeighborCost;

                if (currentCost < shortestPathLength) {
                    bestPath = currentPath;
                    shortestPathLength = currentCost;
                }

                addTabu(currentPath);
            } else {
                // Diversify if no improvement
//                currentPath = generateInitialPath(size);
                diversify(currentPath);
                currentCost = calculatePathCost(currentPath, graph);
                std::cout << "new cost after diversification: " << currentCost << std::endl;
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
