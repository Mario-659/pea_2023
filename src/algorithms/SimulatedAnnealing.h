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
    SimulatedAnnealing(double initialCoolingRatio = 0.9999999, int timeLimit = 10);
    void solve(AdjacencyMatrix& graph) override;
    std::string toString() override;

private:
    int verticesNumber;
    double temperature;
    double coolingRatio;
    int timeLimit;
    std::vector<int> path;
    std::vector<std::vector<int>> routes;

    int getPathCost(const std::vector<int>& pathInstance);
    double getInitialTemperature();
    std::vector<int> getDefaultPath();
    std::vector<int> swapElementsInPath(const std::vector<int>& oldPath);
};

#endif //PEA_SIMULATEDANNEALING_H
