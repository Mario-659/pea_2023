#ifndef PEA_GENETIC_H
#define PEA_GENETIC_H

#include "TSPSolver.h"

using namespace std;

class Genetic : public TSPSolver {
public:
    int verticesNumber;
    vector<vector<int>> routes;
    vector<int> path;
    double mutationRate = 0.01;
    double crossoverRate = 0.8;
    int mutationType = 1;
    int timeLimit = 120;
    int populationSize = 500;

    std::vector<int> bestPath;

    vector<int> getDefaultPath() const;
    vector<int> orderCrossover(vector<int> firstParent, vector<int> secondParent) const;
    vector<int> inversionMutation(vector<int> pathToMutate) const;
    vector<int> swapMutation(vector<int> pathToMutate) const;

    void solve(AdjacencyMatrix &graph) override;

    std::string toString() override;

    int getPathCost(vector<int> pathInstance, AdjacencyMatrix &graph);
};


#endif //PEA_GENETIC_H
