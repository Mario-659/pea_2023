#ifndef PEA_BRANCHANDBOUND_H
#define PEA_BRANCHANDBOUND_H

#include "../graphs/AdjacencyMatrix.h"

#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <algorithm>
#include <sstream>

struct BaBNode {
    std::vector<int> path;
    int level;
    int bound;
    bool operator<(const BaBNode& other) const {
        return bound < other.bound;
    }
};

class BranchAndBound {
private:

    int minCost;
    int size;
    std::vector<int> bestPath;

    int TSPBound(AdjacencyMatrix &matrix, BaBNode u);
    void findPath(AdjacencyMatrix &graph);

public:

    BranchAndBound() : minCost(INT_MAX), size(0) {}

    void solve(AdjacencyMatrix &graph);

    int getMinCost() const { return minCost; }

    std::string toString();
};

#endif //PEA_BRANCHANDBOUND_H
