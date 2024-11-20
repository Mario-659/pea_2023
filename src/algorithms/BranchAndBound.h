#ifndef PEA_BRANCHANDBOUND_H
#define PEA_BRANCHANDBOUND_H

#include <vector>
#include <string>
#include <bitset>
#include "TSPSolver.h"
#include "../graphs/AdjacencyMatrix.h"

struct Node {
    int level;
    int pathCost;
    int bound;
    std::vector<int> path;
    std::vector<bool> visited; // Replace with appropriate size based on max nodes

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
    std::vector<int> minOutgoingEdges;

    int calculateBound(const AdjacencyMatrix &graph, const Node &node);
    void precomputeMinEdges(const AdjacencyMatrix &graph);
public:
    BranchAndBound();
    void solve(AdjacencyMatrix &graph) override;
    std::string toString() override;
};

#endif //PEA_BRANCHANDBOUND_H

