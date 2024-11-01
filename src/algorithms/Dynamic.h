#ifndef PEA_DYNAMIC_H
#define PEA_DYNAMIC_H

#include <vector>
#include <climits>
#include <string>
#include <algorithm>

#include "TSPSolver.h"
#include "../graphs/AdjacencyMatrix.h"

class Dynamic : public TSPSolver {
private:
    std::vector<int> bestPath;
    AdjacencyMatrix* graph;
    std::vector<std::vector<int>> memo;
    std::vector<std::vector<int>> parent;

    // recursive function to calculate the minimum weight of the TSP
    int findMinConst(int pos, int visited);
    // builds the path based on the parent table
    void buildPath();
    // initializes memoization and parent tables
    void initializeTables();

public:
    Dynamic();

    void solve(AdjacencyMatrix &graph) override;

    std::string toString() override;
};

#endif //PEA_DYNAMIC_H
