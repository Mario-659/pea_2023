#ifndef SDIZO_2_BELLMANFORD_H
#define SDIZO_2_BELLMANFORD_H

#include "Heap.h"
#include "../graphs/AdjacencyList.h"
#include "../graphs/AdjacencyMatrix.h"

#include <string>

class BellmanFord {
private:
    // p of the predecessors
    int* p;

    // connections of the predecessors
    int* connections;

    int size;

    int start;
public:

    void shortestPath(AdjacencyMatrix graph, int start);

    void shortestPath(AdjacencyList graph, int start);

    int* getWeights();

    int* getPredeccesorArray();

    int getPathLen(int end);

    BellmanFord();

    ~BellmanFord();

    std::string toString();
};


#endif //SDIZO_2_BELLMANFORD_H
