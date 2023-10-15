#ifndef PEA_BRUTEFORCE_H
#define PEA_BRUTEFORCE_H

#include "../graphs/AdjacencyMatrix.h"

#include <algorithm>
#include <climits>
#include <vector>
#include <string>

class BruteForce {
private:
    int shortestPathLength;
    int size;
    std::vector<int> bestPath;

public:

    BruteForce() : shortestPathLength(INT_MAX), size(0) {}

    void findShortestPath(AdjacencyMatrix &graph);

    int getShortestPathLength() const { return shortestPathLength; }

    std::string toString();

};

#endif //PEA_BRUTEFORCE_H
