#ifndef PEA_TSPSOLVER_H
#define PEA_TSPSOLVER_H

#include <vector>
#include <string>
#include <limits>
#include <climits>

#include "../graphs/AdjacencyMatrix.h"


class TSPSolver {
protected:
    int shortestPathLength;
    int size;
public:
    TSPSolver() : shortestPathLength(INT_MAX), size(0) {}

    virtual void solve(AdjacencyMatrix &graph) = 0;

    int getShortestPathLength() const { return shortestPathLength; }

    virtual std::string toString() = 0;

    virtual ~TSPSolver() = default;
};

#endif //PEA_TSPSOLVER_H
