#ifndef PEA_TABUSEARCH_H
#define PEA_TABUSEARCH_H

#include "TSPSolver.h"
#include "../graphs/AdjacencyMatrix.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>

class TabuSearch : public TSPSolver {
public:
    TabuSearch(int timeLimit = 5);
    void solve(AdjacencyMatrix& graph) override;
    std::string toString() override;

private:
    int verticesNumber;
    int timeLimit;
    std::vector<int> path;
    std::vector<std::vector<int>> routes;

    int getPathCost(const std::vector<int>& pathInstance);
    std::vector<int> getDefaultTabuPath();
    std::vector<int> generateRandomPath();
};

#endif // PEA_TABUSEARCH_H
