#ifndef PEA_GREEDY_H
#define PEA_GREEDY_H

#include <vector>
#include <string>
#include <limits>
#include <climits>

#include "../graphs/AdjacencyMatrix.h"


class Greedy {
protected:
    int shortestPathLength;
    int size;
public:
    std::vector<int> path;
    Greedy() : shortestPathLength(INT_MAX), size(0) {}

    void solve(AdjacencyMatrix &graph, int startingVertex);
    void solve(AdjacencyMatrix &graph);

    int getShortestPathLength() const { return shortestPathLength; }

    std::string toString();

    ~Greedy() = default;
};


#endif //PEA_GREEDY_H
