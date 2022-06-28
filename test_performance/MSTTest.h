#ifndef SDIZO_2_MSTTEST_H
#define SDIZO_2_MSTTEST_H

#include <chrono>

#include "graphs/AdjacencyMatrix.h"
#include "graphs/AdjacencyList.h"
#include "algorithms/Prim.h"
#include "algorithms/Kruskal.h"
#include "utils/Utils.h"

class MSTTest {
private:
    AdjacencyList* listGraph;
    AdjacencyMatrix* matrixGraph;

    double listResult;
    double matrixResult;
public:
    void runPrimTest(int graphSize, int density);

    void runKruskalTest(int graphSize, int density);

    double getListResult();

    double getMatrixResult();
};


#endif //SDIZO_2_MSTTEST_H
