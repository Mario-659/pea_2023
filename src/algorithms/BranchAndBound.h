#ifndef PEA_BRANCHANDBOUND_H
#define PEA_BRANCHANDBOUND_H

#include <vector>
#include <string>
#include <queue>

#include "TSPSolver.h"
#include "../graphs/AdjacencyMatrix.h"

struct Node {
    int level;              // Current depth in the search tree
    int pathCost;           // Total cost of reaching this node
    int bound;              // Lower bound of the path from this node
    std::vector<int> path;  // Stores the path taken to reach this node
    std::vector<bool> visited; // Keeps track of visited nodes

    Node(int level, int pathCost, int bound, const std::vector<int>& path, int size)
            : level(level), pathCost(pathCost), bound(bound), path(path), visited(size, false) {}

    Node() = default;

    bool operator<(const Node& other) const {
        return bound > other.bound; // Higher priority for lower bound
    }
    bool operator>(const Node& other) const {
        return bound < other.bound;
    }
};

class BranchAndBound : public TSPSolver {
private:
    std::vector<int> bestPath;
    int minCost;

    // Calculate the bound for the given node
    int calculateBound(const AdjacencyMatrix &graph, const Node &node);

    // Main branch-and-bound solver function
    void solveATSP(const AdjacencyMatrix &graph);

public:
    BranchAndBound();

    void solve(AdjacencyMatrix &graph) override;

    std::string toString() override;
};

#endif //PEA_BRANCHANDBOUND_H
