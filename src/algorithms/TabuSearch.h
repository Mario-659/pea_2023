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
//    1 - swap, 2 - inverse, 3 - twoOptSwap
    void setStrategy(int s);
private:
    int verticesNumber;
    int timeLimit;
    int strategy;
    std::vector<int> path;

    int getPathCost(const std::vector<int>& pathInstance, const AdjacencyMatrix& graph);
    std::vector<int> getDefaultTabuPath();
    std::vector<int> generateRandomPath();

    std::vector<int> twoOptSwap(const std::vector<int> &route, int v1, int v2);
    std::vector<int> inversionMutation(const std::vector<int> &route, int startIdx, int endIdx);
    std::vector<int> swapStrategy(const std::vector<int> &route, int index1, int index2);

    std::vector<int> getNeighbor(const std::vector<int> &route, int v1, int v2);
};

#endif // PEA_TABUSEARCH_H
