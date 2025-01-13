#ifndef PEA_SIMULATEDANNEALING_H
#define PEA_SIMULATEDANNEALING_H

#include "TSPSolver.h"
#include "../graphs/AdjacencyMatrix.h"
#include <vector>
#include <chrono>
#include <random>
#include <numeric>


class SimulatedAnnealing : public TSPSolver {
public:
    SimulatedAnnealing(double initialCoolingRatio = 0.9999999, int timeLimit = 30);
    void solve(AdjacencyMatrix& graph) override;
    void setTimeLimit(std::chrono::seconds timeLimit);
    void setCoolingRatio(double coolRatio);
    std::string toString() override;
    std::vector<int> path;
    double initialTemperature;
    double finalTemperature;
    std::chrono::milliseconds optimalSolutionTime;
private:
    int graphSize;
    double temperature;
    double coolingRatio;
    std::chrono::seconds timeLimit;
    std::vector<std::vector<int>> routes;

    int calculatePathCost(const std::vector<int>& pathInstance, const AdjacencyMatrix& graph);
    double getInitialTemperature(AdjacencyMatrix& graph);
    std::vector<int> getSwapNeighbor(int range, std::vector<int> oldPath);
    std::vector<int> getGreedySolution(AdjacencyMatrix &adjacencyMatrix);
};

#endif //PEA_SIMULATEDANNEALING_H
