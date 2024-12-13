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
private:
    int verticesNumber;
    double temperature;
    double coolingRatio;
    std::chrono::seconds timeLimit;
    std::vector<std::vector<int>> routes;

    int getPathCost(const std::vector<int>& pathInstance, const AdjacencyMatrix& graph);
    double getInitialTemperature(AdjacencyMatrix& graph);
    std::vector<int> getDefaultPath();
    std::vector<int> swapElementsInPath(int range, std::vector<int> oldPath);

};

#endif //PEA_SIMULATEDANNEALING_H
