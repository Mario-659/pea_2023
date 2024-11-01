#ifndef PEA_BRUTEFORCE_H
#define PEA_BRUTEFORCE_H

#include "../graphs/AdjacencyMatrix.h"
#include "TSPSolver.h"

#include <algorithm>
#include <climits>
#include <vector>
#include <string>

class BruteForce : public TSPSolver {
private:
    int size;
    std::vector<int> bestPath;

public:

    BruteForce() : TSPSolver(), size(0) {}

    void solve(AdjacencyMatrix &graph) override;

    std::string toString() override;
};

#endif //PEA_BRUTEFORCE_H
