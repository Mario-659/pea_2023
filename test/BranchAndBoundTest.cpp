#include "gtest/gtest.h"
#include "algorithms/BranchAndBound.h"

TEST(BranchAndBoundTSPTest, shouldFindShortestPathFromMatrixCaseOne) {
    AdjacencyMatrix graph(6);
    graph.addEdge(0, 1, 5);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 4, 3);
    graph.addEdge(4, 3, 5);
    graph.addEdge(3, 5, 1);
    graph.addEdge(5, 0, 2);

    BranchAndBound tsp;
    tsp.solve(graph);

    ASSERT_EQ(19, tsp.getMinCost());
    ASSERT_EQ("0 -> 1 -> 2 -> 4 -> 3 -> 5 -> 0", tsp.toString());
}

TEST(BranchAndBoundTSPTest, shouldFindShortestPathFromUndMatrixCaseOne) {
    AdjacencyMatrix graph(6);
    graph.addUndEdge(0, 1, 5);
    graph.addUndEdge(1, 2, 3);
    graph.addUndEdge(2, 4, 3);
    graph.addUndEdge(3, 4, 3);
    graph.addUndEdge(3, 5, 1);
    graph.addUndEdge(5, 0, 2);

    BranchAndBound tsp;
    tsp.solve(graph);

    ASSERT_EQ(17, tsp.getMinCost());
    EXPECT_TRUE("0 -> 1 -> 2 -> 4 -> 3 -> 5 -> 0" == tsp.toString() ||
                "0 -> 5 -> 3 -> 4 -> 2 -> 1 -> 0" == tsp.toString() );
}

TEST(BranchAndBoundTSPTest, tsp_6_1) {
    AdjacencyMatrix graph(6);
    graph.addEdge(0, 1, 20);
    graph.addEdge(0, 2, 30);
    graph.addEdge(0, 3, 31);
    graph.addEdge(0, 4, 28);
    graph.addEdge(0, 5, 40);

    graph.addEdge(1, 0, 30);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 14);
    graph.addEdge(1, 4, 20);
    graph.addEdge(1, 5, 44);

    graph.addEdge(2, 0, 40);
    graph.addEdge(2, 1, 20);
    graph.addEdge(2, 3, 10);
    graph.addEdge(2, 4, 22);
    graph.addEdge(2, 5, 50);

    graph.addEdge(3, 0, 41);
    graph.addEdge(3, 1, 24);
    graph.addEdge(3, 2, 20);
    graph.addEdge(3, 4, 14);
    graph.addEdge(3, 5, 42);

    graph.addEdge(4, 0, 38);
    graph.addEdge(4, 1, 30);
    graph.addEdge(4, 2, 32);
    graph.addEdge(4, 3, 24);
    graph.addEdge(4, 5, 28);

    graph.addEdge(5, 0, 50);
    graph.addEdge(5, 1, 54);
    graph.addEdge(5, 2, 60);
    graph.addEdge(5, 3, 52);
    graph.addEdge(5, 4, 38);

    BranchAndBound tsp;
    tsp.solve(graph);

    ASSERT_EQ(132, tsp.getMinCost());
    ASSERT_EQ("0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 0", tsp.toString());
}