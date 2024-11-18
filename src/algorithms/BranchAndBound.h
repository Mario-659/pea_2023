#ifndef PEA_BRANCHANDBOUND_H
#define PEA_BRANCHANDBOUND_H

#include <vector>
#include <string>

#include "TSPSolver.h"
#include "../graphs/AdjacencyMatrix.h"

struct Node {
    int level;                 // current depth in the search tree
    int pathCost;              // total cost of reaching this node
    int bound;                 // lower bound of the path from this node
    std::vector<int> path;     // path taken to reach this node
    std::vector<bool> visited; // already visited nodes

    Node(int level, int pathCost, int bound, const std::vector<int>& path, int size)
            : level(level), pathCost(pathCost), bound(bound), path(path), visited(size, false) {}

    Node() = default;

    bool operator<(const Node& other) const {
        return bound > other.bound;
    }
    bool operator>(const Node& other) const {
        return bound < other.bound;
    }
};

class BranchAndBound : public TSPSolver {
private:
    std::vector<int> bestPath;
    int minCost;
    int calculateBound(const AdjacencyMatrix &graph, const Node &node);
public:
    BranchAndBound();
    void solve(AdjacencyMatrix &graph) override;
    std::string toString() override;
};

#endif //PEA_BRANCHANDBOUND_H
