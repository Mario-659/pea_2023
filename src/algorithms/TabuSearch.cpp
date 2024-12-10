#include "TabuSearch.h"
//#include <algorithm>
//#include <limits>
//
//#include <vector>
//#include <queue>
//#include <unordered_set>
//#include <random>
//#include <chrono>
//#include <climits>
//#include <algorithm>
//#include <sstream>
//#include <iostream>
//
//class TabuSearch : public TSPSolver {
//private:
//    std::vector<int> bestPath;
//    int diversificationFactor; // Helps escape local optima
//    std::chrono::milliseconds timeLimit;
//    std::vector<std::vector<int>> tabuList;
//    int maxTabuSize;
//
//    enum NeighborhoodStrategy { SWAP, REVERSE, INSERT };
//    NeighborhoodStrategy strategy;
//
//    // Helper to generate a random number in range [low, high]
//    int randomInt(int low, int high) {
//        static std::random_device rd;
//        static std::mt19937 gen(rd());
//        std::uniform_int_distribution<> dis(low, high);
//        return dis(gen);
//    }
//
//    // Helper to calculate the cost of a given path
//    int calculatePathCost(const std::vector<int>& path, AdjacencyMatrix& graph) {
//        int cost = 0;
//        for (size_t i = 0; i < path.size() - 1; ++i) {
//            cost += graph.getEdgeWeight(path[i], path[i + 1]);
//        }
//        cost += graph.getEdgeWeight(path.back(), path.front());
//        return cost;
//    }
//
//    // Generate initial random path
//    std::vector<int> generateInitialPath(int size) {
//        std::vector<int> path(size);
//        std::iota(path.begin(), path.end(), 0);
//        std::shuffle(path.begin(), path.end(), std::mt19937{ std::random_device{}() });
//        return path;
//    }
//
//    // Generate neighborhoods
//    std::vector<std::vector<int>> generateNeighborhood(const std::vector<int>& path) {
//        std::vector<std::vector<int>> neighborhood;
//
//        switch (strategy) {
//            case SWAP:
//                for (size_t i = 0; i < path.size(); ++i) {
//                    for (size_t j = i + 1; j < path.size(); ++j) {
//                        std::vector<int> newPath = path;
//                        std::swap(newPath[i], newPath[j]);
//                        neighborhood.push_back(newPath);
//                    }
//                }
//                break;
//
//            case REVERSE:
//                for (size_t i = 0; i < path.size(); ++i) {
//                    for (size_t j = i + 1; j < path.size(); ++j) {
//                        std::vector<int> newPath = path;
//                        std::reverse(newPath.begin() + i, newPath.begin() + j + 1);
//                        neighborhood.push_back(newPath);
//                    }
//                }
//                break;
//
//            case INSERT:
//                for (size_t i = 0; i < path.size(); ++i) {
//                    for (size_t j = 0; j < path.size(); ++j) {
//                        if (i == j) continue;
//                        std::vector<int> newPath = path;
//                        int city = newPath[i];
//                        newPath.erase(newPath.begin() + i);
//                        newPath.insert(newPath.begin() + j, city);
//                        neighborhood.push_back(newPath);
//                    }
//                }
//                break;
//        }
//
//        return neighborhood;
//    }
//
//    // Check if path is tabu
//    bool isTabu(const std::vector<int>& path) {
//        for (const auto& tabuPath : tabuList) {
//            if (tabuPath == path) {
//                return true;
//            }
//        }
//        return false;
//    }
//
//    // Add path to tabu list
//    void addTabu(const std::vector<int>& path) {
//        if (tabuList.size() >= maxTabuSize) {
//            tabuList.erase(tabuList.begin());
//        }
//        tabuList.push_back(path);
//    }
//
//public:
//    TabuSearch(int diversificationFactor, int maxTabuSize, std::chrono::milliseconds timeLimit, NeighborhoodStrategy strategy)
//            : diversificationFactor(diversificationFactor), maxTabuSize(maxTabuSize), timeLimit(timeLimit), strategy(strategy) {}
//
//    void solve(AdjacencyMatrix& graph) override {
//        auto start = std::chrono::high_resolution_clock::now();
//        size = graph.getSize();
//        bestPath = generateInitialPath(size);
//        shortestPathLength = calculatePathCost(bestPath, graph);
//
//        std::vector<int> currentPath = bestPath;
//        int currentCost = shortestPathLength;
//
//        while (true) {
//            auto now = std::chrono::high_resolution_clock::now();
//            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start) > timeLimit) {
//                break;
//            }
//
//            auto neighborhood = generateNeighborhood(currentPath);
//            std::vector<int> bestNeighbor;
//            int bestNeighborCost = INT_MAX;
//
//            for (const auto& neighbor : neighborhood) {
//                if (isTabu(neighbor)) continue;
//
//                int cost = calculatePathCost(neighbor, graph);
//                if (cost < bestNeighborCost) {
//                    bestNeighbor = neighbor;
//                    bestNeighborCost = cost;
//                }
//            }
//
//            if (!bestNeighbor.empty()) {
//                currentPath = bestNeighbor;
//                currentCost = bestNeighborCost;
//
//                if (currentCost < shortestPathLength) {
//                    bestPath = currentPath;
//                    shortestPathLength = currentCost;
//                }
//
//                addTabu(currentPath);
//            } else {
//                // Diversify if no improvement
//                currentPath = generateInitialPath(size);
//                currentCost = calculatePathCost(currentPath, graph);
//            }
//        }
//    }
//
//    std::string toString() override {
//        std::ostringstream oss;
//        oss << "Shortest Path Length: " << shortestPathLength << "\nPath: ";
//        for (int node : bestPath) {
//            oss << node << " -> ";
//        }
//        oss << bestPath[0]; // Close the cycle
//        return oss.str();
//    }
//};
//
//
//std::string TabuSearch::toString() {
//    std::string result;
//    for (int city : path) {
//        result += std::to_string(city) + " -> ";
//    }
//    result += std::to_string(path[0]);
//    return result;
//}
//
//void TabuSearch::setStrategy(int s) {
//    strategy = s;
//}
//
//void TabuSearch::setTimeLimit(int time) {
//    timeLimit = time;
//}
