#include "PathTest.h"

using namespace std::chrono;

void PathTest::runDijkstraTest(int graphSize, int density) {
    listResult = 0;
    matrixResult = 0;

    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;

    Dijkstra dijkstra;

    for (int i=0; i<50; i++) {
        utils::generateRandomDirectedGraphs(matrixGraph, listGraph, graphSize, density);

        std:: cout << i << " ";

        t1 = high_resolution_clock::now();
        dijkstra.shortestPath(*listGraph, 0);
        t2 = high_resolution_clock::now();
        duration<double> timeElapsed = duration_cast<duration<double>>(t2 - t1);
        listResult += timeElapsed.count();

        t1 = high_resolution_clock::now();
        dijkstra.shortestPath(*matrixGraph, 0);
        t2 = high_resolution_clock::now();
        timeElapsed = duration_cast<duration<double>>(t2 - t1);
        matrixResult += timeElapsed.count();
    }
    matrixResult /= 50;
    listResult /= 50;
}

void PathTest::runBellmanTest(int graphSize, int density) {
    listResult = 0;
    matrixResult = 0;

    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;

    BellmanFord bellman;

    for (int i=0; i<50; i++) {
        utils::generateRandomDirectedGraphs(matrixGraph, listGraph, graphSize, density);

        t1 = high_resolution_clock::now();
        bellman.shortestPath(*listGraph, 0);
        t2 = high_resolution_clock::now();
        duration<double> timeElapsed = duration_cast<duration<double>>(t2 - t1);
        listResult += timeElapsed.count();

        t1 = high_resolution_clock::now();
        bellman.shortestPath(*matrixGraph, 0);
        t2 = high_resolution_clock::now();
        timeElapsed = duration_cast<duration<double>>(t2 - t1);
        matrixResult += timeElapsed.count();
    }
    matrixResult /= 50;
    listResult /= 50;
}

double PathTest::getListResult() {
    return listResult;
}

double PathTest::getMatrixResult() {
    return matrixResult;
}
