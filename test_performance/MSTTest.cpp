#include "MSTTest.h"

using namespace std::chrono;

void MSTTest::runPrimTest(int graphSize, int density) {
    listResult = 0;
    matrixResult = 0;

    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;

    Prim prim;

    for (int i=0; i<50; i++) {
        utils::generateRandomUndirectedGraphs(matrixGraph, listGraph, graphSize, density);

        std:: cout << i << " ";

        t1 = high_resolution_clock::now();
        prim.mst(*listGraph);
        t2 = high_resolution_clock::now();
        duration<double> timeElapsed = duration_cast<duration<double>>(t2 - t1);
        listResult += timeElapsed.count();

        t1 = high_resolution_clock::now();
        prim.mst(*matrixGraph);
        t2 = high_resolution_clock::now();
        timeElapsed = duration_cast<duration<double>>(t2 - t1);
        matrixResult += timeElapsed.count();
    }
    matrixResult /= 50;
    listResult /= 50;
}

void MSTTest::runKruskalTest(int graphSize, int density) {
    listResult = 0;
    matrixResult = 0;

    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;

    Kruskal kruskal;

    for (int i=0; i<50; i++) {
        utils::generateRandomUndirectedGraphs(matrixGraph, listGraph, graphSize, density);

        std::cout << i << std::endl;

        t1 = high_resolution_clock::now();
        kruskal.mst(*listGraph);
        t2 = high_resolution_clock::now();
        duration<double> timeElapsed = duration_cast<duration<double>>(t2 - t1);
        listResult += timeElapsed.count();

        t1 = high_resolution_clock::now();
        kruskal.mst(*matrixGraph);
        t2 = high_resolution_clock::now();
        timeElapsed = duration_cast<duration<double>>(t2 - t1);
        matrixResult += timeElapsed.count();
    }
    matrixResult /= 50;
    listResult /= 50;
}

double MSTTest::getListResult() {
    return listResult;
}

double MSTTest::getMatrixResult() {
    return matrixResult;
}
