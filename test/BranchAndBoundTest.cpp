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

TEST(BranchAndBoundTSPTest, tsp_6_2) {
    AdjacencyMatrix graph(6);
    graph.addEdge(0, 1, 20);
    graph.addEdge(0, 2, 30);
    graph.addEdge(0, 3, 31);
    graph.addEdge(0, 4, 28);
    graph.addEdge(0, 5, 4);

    graph.addEdge(1, 0, 30);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 4);
    graph.addEdge(1, 4, 20);
    graph.addEdge(1, 5, 44);

    graph.addEdge(2, 0, 40);
    graph.addEdge(2, 1, 20);
    graph.addEdge(2, 3, 10);
    graph.addEdge(2, 4, 22);
    graph.addEdge(2, 5, 50);

    graph.addEdge(3, 0, 41);
    graph.addEdge(3, 1, 4);
    graph.addEdge(3, 2, 20);
    graph.addEdge(3, 4, 14);
    graph.addEdge(3, 5, 42);

    graph.addEdge(4, 0, 38);
    graph.addEdge(4, 1, 30);
    graph.addEdge(4, 2, 32);
    graph.addEdge(4, 3, 4);
    graph.addEdge(4, 5, 28);

    graph.addEdge(5, 0, 50);
    graph.addEdge(5, 1, 4);
    graph.addEdge(5, 2, 60);
    graph.addEdge(5, 3, 52);
    graph.addEdge(5, 4, 38);

    BranchAndBound tsp;
    tsp.solve(graph);

    ASSERT_EQ(80, tsp.getMinCost());
    ASSERT_EQ("0 -> 5 -> 1 -> 2 -> 3 -> 4 -> 0", tsp.toString());
}

TEST(BranchAndBoundTSPTest, tsp_10_1) {
    AdjacencyMatrix graph(10);
    graph.addEdge(0, 1, 81);
    graph.addEdge(0, 2, 50);
    graph.addEdge(0, 3, 18);
    graph.addEdge(0, 4, 75);
    graph.addEdge(0, 5, 39);
    graph.addEdge(0, 6, 107);
    graph.addEdge(0, 7, 77);
    graph.addEdge(0, 8, 87);
    graph.addEdge(0, 9, 43);

    graph.addEdge(1, 0, 81);
    graph.addEdge(1, 2, 76);
    graph.addEdge(1, 3, 21);
    graph.addEdge(1, 4, 37);
    graph.addEdge(1, 5, 26);
    graph.addEdge(1, 6, 34);
    graph.addEdge(1, 7, 58);
    graph.addEdge(1, 8, 66);
    graph.addEdge(1, 9, 15);

    graph.addEdge(2, 0, 50);
    graph.addEdge(2, 1, 76);
    graph.addEdge(2, 3, 24);
    graph.addEdge(2, 4, 14);
    graph.addEdge(2, 5, 58);
    graph.addEdge(2, 6, 100);
    graph.addEdge(2, 7, 68);
    graph.addEdge(2, 8, 33);
    graph.addEdge(2, 9, 30);

    graph.addEdge(3, 0, 18);
    graph.addEdge(3, 1, 21);
    graph.addEdge(3, 2, 24);
    graph.addEdge(3, 4, 19);
    graph.addEdge(3, 5, 58);
    graph.addEdge(3, 6, 68);
    graph.addEdge(3, 7, 62);
    graph.addEdge(3, 8, 84);
    graph.addEdge(3, 9, 81);

    graph.addEdge(4, 0, 75);
    graph.addEdge(4, 1, 37);
    graph.addEdge(4, 2, 14);
    graph.addEdge(4, 3, 19);
    graph.addEdge(4, 5, 31);
    graph.addEdge(4, 6, 60);
    graph.addEdge(4, 7, 65);
    graph.addEdge(4, 8, 29);
    graph.addEdge(4, 9, 91);

    graph.addEdge(5, 0, 39);
    graph.addEdge(5, 1, 26);
    graph.addEdge(5, 2, 58);
    graph.addEdge(5, 3, 58);
    graph.addEdge(5, 4, 31);
    graph.addEdge(5, 6, 64);
    graph.addEdge(5, 7, 21);
    graph.addEdge(5, 8, 42);
    graph.addEdge(5, 9, 46);

    graph.addEdge(6, 0, 107);
    graph.addEdge(6, 1, 34);
    graph.addEdge(6, 2, 100);
    graph.addEdge(6, 3, 68);
    graph.addEdge(6, 4, 60);
    graph.addEdge(6, 5, 64);
    graph.addEdge(6, 7, 15);
    graph.addEdge(6, 8, 55);
    graph.addEdge(6, 9, 16);

    graph.addEdge(7, 0, 77);
    graph.addEdge(7, 1, 58);
    graph.addEdge(7, 2, 68);
    graph.addEdge(7, 3, 62);
    graph.addEdge(7, 4, 65);
    graph.addEdge(7, 5, 21);
    graph.addEdge(7, 6, 15);
    graph.addEdge(7, 8, 17);
    graph.addEdge(7, 9, 34);

    graph.addEdge(8, 0, 87);
    graph.addEdge(8, 1, 66);
    graph.addEdge(8, 2, 33);
    graph.addEdge(8, 3, 84);
    graph.addEdge(8, 4, 29);
    graph.addEdge(8, 5, 42);
    graph.addEdge(8, 6, 55);
    graph.addEdge(8, 7, 17);
    graph.addEdge(8, 9, 68);

    graph.addEdge(9, 0, 43);
    graph.addEdge(9, 1, 15);
    graph.addEdge(9, 2, 30);
    graph.addEdge(9, 3, 81);
    graph.addEdge(9, 4, 91);
    graph.addEdge(9, 5, 46);
    graph.addEdge(9, 6, 16);
    graph.addEdge(9, 7, 34);
    graph.addEdge(9, 8, 68);

    BranchAndBound tsp;
    tsp.solve(graph);

//    ASSERT_EQ(212, tsp.getMinCost());
    ASSERT_EQ("0 -> 3 -> 4 -> 2 -> 8 -> 7 -> 6 -> 9 -> 1 -> 5 -> 0", tsp.toString());
}
