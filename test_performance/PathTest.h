#ifndef SDIZO_2_PATHTEST_H
#define SDIZO_2_PATHTEST_H

#include <chrono>

#include "graphs/AdjacencyMatrix.h"
#include "graphs/AdjacencyList.h"
#include "algorithms/BellmanFord.h"
#include "algorithms/Dijkstra.h"
#include "utils/Utils.h"

class PathTest {
    AdjacencyList* listGraph;
    AdjacencyMatrix* matrixGraph;

    double listResult;
    double matrixResult;
public:
    void runDijkstraTest(int graphSize, int density);

    void runBellmanTest(int graphSize, int density);

    double getListResult();

    double getMatrixResult();
};


#endif //SDIZO_2_PATHTEST_H
