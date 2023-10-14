#include "gtest/gtest.h"
#include "algorithms/BruteForce.h"

TEST(BruteForceTSPTest, shouldFindShortestPathFromMatrixCaseOne) {
    AdjacencyMatrix graph(6);
    graph.addEdge(0, 1, 5);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 4, 3);
    graph.addEdge(4, 3, 5);
    graph.addEdge(3, 5, 1);
    graph.addEdge(5, 0, 2);

    BruteForce tsp;
    tsp.findShortestPath(graph);

    ASSERT_EQ(19, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 1 -> 2 -> 4 -> 3 -> 5 -> 0", tsp.toString());
}

TEST(BruteForceTSPTest, shouldFindShortestPathFromUndMatrixCaseOne) {
    AdjacencyMatrix graph(6);
    graph.addUndEdge(0, 1, 5);
    graph.addUndEdge(1, 2, 3);
    graph.addUndEdge(2, 4, 3);
    graph.addUndEdge(3, 4, 3);
    graph.addUndEdge(3, 5, 1);
    graph.addUndEdge(5, 0, 2);

    BruteForce tsp;
    tsp.findShortestPath(graph);

    ASSERT_EQ(17, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 1 -> 2 -> 4 -> 3 -> 5 -> 0", tsp.toString());
}
