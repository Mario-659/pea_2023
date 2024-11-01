#include "gtest/gtest.h"
#include "algorithms/BruteForce.h"

TEST(BruteForceTSPTest, shouldFindShortestPathFromMatrixCaseOne) {
    AdjacencyMatrix graph(6);
    graph.setEdge(0, 1, 5);
    graph.setEdge(1, 2, 3);
    graph.setEdge(2, 4, 3);
    graph.setEdge(3, 4, 3);
    graph.setEdge(4, 3, 5);
    graph.setEdge(3, 5, 1);
    graph.setEdge(5, 0, 2);

    BruteForce tsp;
    tsp.solve(graph);

    ASSERT_EQ(19, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 1 -> 2 -> 4 -> 3 -> 5 -> 0", tsp.toString());
}

TEST(BruteForceTSPTest, shouldFindShortestPathFromUndMatrixCaseOne) {
    AdjacencyMatrix graph(6);
    graph.setEdge(0, 1, 5);
    graph.setEdge(1, 0, 5);

    graph.setEdge(1, 2, 3);
    graph.setEdge(2, 1, 3);

    graph.setEdge(2, 4, 3);
    graph.setEdge(4, 2, 3);

    graph.setEdge(3, 4, 3);
    graph.setEdge(4, 3, 3);

    graph.setEdge(3, 5, 1);
    graph.setEdge(5, 3, 1);

    graph.setEdge(5, 0, 2);
    graph.setEdge(0, 5, 2);

    BruteForce tsp;
    tsp.solve(graph);

    ASSERT_EQ(17, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 1 -> 2 -> 4 -> 3 -> 5 -> 0", tsp.toString());
}

TEST(BruteForceTSPTest, shouldFindShortestPathFromUndirectedMatrixRandomCaseOne) {
    AdjacencyMatrix graph(4);
    graph.setEdge(0, 1, 11);
    graph.setEdge(0, 2, 71);
    graph.setEdge(0, 3, 93);
    graph.setEdge(1, 0, 9);
    graph.setEdge(1, 2, 29);
    graph.setEdge(1, 3, 30);
    graph.setEdge(2, 0, 66);
    graph.setEdge(2, 1, 77);
    graph.setEdge(2, 3, 16);
    graph.setEdge(3, 0, 2);
    graph.setEdge(3, 1, 14);
    graph.setEdge(3, 2, 87);

    BruteForce tsp;
    tsp.solve(graph);

    ASSERT_EQ(58, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 1 -> 2 -> 3 -> 0", tsp.toString());
}


TEST(BruteForceTSPTest, shouldFindShortestPathFromUndirectedMatrixRandomCaseTwo) {
    AdjacencyMatrix graph(5);
    graph.setEdge(0, 1, 55);
    graph.setEdge(0, 2, 47);
    graph.setEdge(0, 3, 63);
    graph.setEdge(0, 4, 29);

    graph.setEdge(1, 0, 39);
    graph.setEdge(1, 2, 22);
    graph.setEdge(1, 3, 35);
    graph.setEdge(1, 4, 3);

    graph.setEdge(2, 0, 91);
    graph.setEdge(2, 1, 26);
    graph.setEdge(2, 3, 3);
    graph.setEdge(2, 4, 98);

    graph.setEdge(3, 0, 13);
    graph.setEdge(3, 1, 13);
    graph.setEdge(3, 2, 84);
    graph.setEdge(3, 4, 69);

    graph.setEdge(4, 0, 8);
    graph.setEdge(4, 1, 69);
    graph.setEdge(4, 2, 34);
    graph.setEdge(4, 3, 62);

    BruteForce tsp;
    tsp.solve(graph);

    ASSERT_EQ(74, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 2 -> 3 -> 1 -> 4 -> 0", tsp.toString());
}

TEST(BruteForceTSPTest, tsp_6_1) {
    AdjacencyMatrix graph(6);
    graph.setEdge(0, 1, 20);
    graph.setEdge(0, 2, 30);
    graph.setEdge(0, 3, 31);
    graph.setEdge(0, 4, 28);
    graph.setEdge(0, 5, 40);

    graph.setEdge(1, 0, 30);
    graph.setEdge(1, 2, 10);
    graph.setEdge(1, 3, 14);
    graph.setEdge(1, 4, 20);
    graph.setEdge(1, 5, 44);

    graph.setEdge(2, 0, 40);
    graph.setEdge(2, 1, 20);
    graph.setEdge(2, 3, 10);
    graph.setEdge(2, 4, 22);
    graph.setEdge(2, 5, 50);

    graph.setEdge(3, 0, 41);
    graph.setEdge(3, 1, 24);
    graph.setEdge(3, 2, 20);
    graph.setEdge(3, 4, 14);
    graph.setEdge(3, 5, 42);

    graph.setEdge(4, 0, 38);
    graph.setEdge(4, 1, 30);
    graph.setEdge(4, 2, 32);
    graph.setEdge(4, 3, 24);
    graph.setEdge(4, 5, 28);

    graph.setEdge(5, 0, 50);
    graph.setEdge(5, 1, 54);
    graph.setEdge(5, 2, 60);
    graph.setEdge(5, 3, 52);
    graph.setEdge(5, 4, 38);

    BruteForce tsp;
    tsp.solve(graph);

    ASSERT_EQ(132, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 0", tsp.toString());
}


TEST(BruteForceTSPTest, tsp_6_2) {
    AdjacencyMatrix graph(6);
    graph.setEdge(0, 1, 20);
    graph.setEdge(0, 2, 30);
    graph.setEdge(0, 3, 31);
    graph.setEdge(0, 4, 28);
    graph.setEdge(0, 5, 4);

    graph.setEdge(1, 0, 30);
    graph.setEdge(1, 2, 10);
    graph.setEdge(1, 3, 4);
    graph.setEdge(1, 4, 20);
    graph.setEdge(1, 5, 44);

    graph.setEdge(2, 0, 40);
    graph.setEdge(2, 1, 20);
    graph.setEdge(2, 3, 10);
    graph.setEdge(2, 4, 22);
    graph.setEdge(2, 5, 50);

    graph.setEdge(3, 0, 41);
    graph.setEdge(3, 1, 4);
    graph.setEdge(3, 2, 20);
    graph.setEdge(3, 4, 14);
    graph.setEdge(3, 5, 42);

    graph.setEdge(4, 0, 38);
    graph.setEdge(4, 1, 30);
    graph.setEdge(4, 2, 32);
    graph.setEdge(4, 3, 4);
    graph.setEdge(4, 5, 28);

    graph.setEdge(5, 0, 50);
    graph.setEdge(5, 1, 4);
    graph.setEdge(5, 2, 60);
    graph.setEdge(5, 3, 52);
    graph.setEdge(5, 4, 38);

    BruteForce tsp;
    tsp.solve(graph);

    ASSERT_EQ(80, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 5 -> 1 -> 2 -> 3 -> 4 -> 0", tsp.toString());
}

TEST(BruteForceTSPTest, tsp_10_1) {
    AdjacencyMatrix graph(10);
    graph.setEdge(0, 1, 81);
    graph.setEdge(0, 2, 50);
    graph.setEdge(0, 3, 18);
    graph.setEdge(0, 4, 75);
    graph.setEdge(0, 5, 39);
    graph.setEdge(0, 6, 107);
    graph.setEdge(0, 7, 77);
    graph.setEdge(0, 8, 87);
    graph.setEdge(0, 9, 43);

    graph.setEdge(1, 0, 81);
    graph.setEdge(1, 2, 76);
    graph.setEdge(1, 3, 21);
    graph.setEdge(1, 4, 37);
    graph.setEdge(1, 5, 26);
    graph.setEdge(1, 6, 34);
    graph.setEdge(1, 7, 58);
    graph.setEdge(1, 8, 66);
    graph.setEdge(1, 9, 15);

    graph.setEdge(2, 0, 50);
    graph.setEdge(2, 1, 76);
    graph.setEdge(2, 3, 24);
    graph.setEdge(2, 4, 14);
    graph.setEdge(2, 5, 58);
    graph.setEdge(2, 6, 100);
    graph.setEdge(2, 7, 68);
    graph.setEdge(2, 8, 33);
    graph.setEdge(2, 9, 30);

    graph.setEdge(3, 0, 18);
    graph.setEdge(3, 1, 21);
    graph.setEdge(3, 2, 24);
    graph.setEdge(3, 4, 19);
    graph.setEdge(3, 5, 58);
    graph.setEdge(3, 6, 68);
    graph.setEdge(3, 7, 62);
    graph.setEdge(3, 8, 84);
    graph.setEdge(3, 9, 81);

    graph.setEdge(4, 0, 75);
    graph.setEdge(4, 1, 37);
    graph.setEdge(4, 2, 14);
    graph.setEdge(4, 3, 19);
    graph.setEdge(4, 5, 31);
    graph.setEdge(4, 6, 60);
    graph.setEdge(4, 7, 65);
    graph.setEdge(4, 8, 29);
    graph.setEdge(4, 9, 91);

    graph.setEdge(5, 0, 39);
    graph.setEdge(5, 1, 26);
    graph.setEdge(5, 2, 58);
    graph.setEdge(5, 3, 58);
    graph.setEdge(5, 4, 31);
    graph.setEdge(5, 6, 64);
    graph.setEdge(5, 7, 21);
    graph.setEdge(5, 8, 42);
    graph.setEdge(5, 9, 46);

    graph.setEdge(6, 0, 107);
    graph.setEdge(6, 1, 34);
    graph.setEdge(6, 2, 100);
    graph.setEdge(6, 3, 68);
    graph.setEdge(6, 4, 60);
    graph.setEdge(6, 5, 64);
    graph.setEdge(6, 7, 15);
    graph.setEdge(6, 8, 55);
    graph.setEdge(6, 9, 16);

    graph.setEdge(7, 0, 77);
    graph.setEdge(7, 1, 58);
    graph.setEdge(7, 2, 68);
    graph.setEdge(7, 3, 62);
    graph.setEdge(7, 4, 65);
    graph.setEdge(7, 5, 21);
    graph.setEdge(7, 6, 15);
    graph.setEdge(7, 8, 17);
    graph.setEdge(7, 9, 34);

    graph.setEdge(8, 0, 87);
    graph.setEdge(8, 1, 66);
    graph.setEdge(8, 2, 33);
    graph.setEdge(8, 3, 84);
    graph.setEdge(8, 4, 29);
    graph.setEdge(8, 5, 42);
    graph.setEdge(8, 6, 55);
    graph.setEdge(8, 7, 17);
    graph.setEdge(8, 9, 68);

    graph.setEdge(9, 0, 43);
    graph.setEdge(9, 1, 15);
    graph.setEdge(9, 2, 30);
    graph.setEdge(9, 3, 81);
    graph.setEdge(9, 4, 91);
    graph.setEdge(9, 5, 46);
    graph.setEdge(9, 6, 16);
    graph.setEdge(9, 7, 34);
    graph.setEdge(9, 8, 68);

    BruteForce tsp;
    tsp.solve(graph);

    ASSERT_EQ(212, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 3 -> 4 -> 2 -> 8 -> 7 -> 6 -> 9 -> 1 -> 5 -> 0", tsp.toString());
}

TEST(BruteForceTSPTest, tsp_12_1) {
    AdjacencyMatrix graph(12);
    graph.setEdge(0, 1, 29);
    graph.setEdge(0, 2, 82);
    graph.setEdge(0, 3, 46);
    graph.setEdge(0, 4, 68);
    graph.setEdge(0, 5, 52);
    graph.setEdge(0, 6, 72);
    graph.setEdge(0, 7, 42);
    graph.setEdge(0, 8, 51);
    graph.setEdge(0, 9, 55);
    graph.setEdge(0, 10, 29);
    graph.setEdge(0, 11, 74);

    graph.setEdge(1, 0, 29);
    graph.setEdge(1, 2, 55);
    graph.setEdge(1, 3, 46);
    graph.setEdge(1, 4, 42);
    graph.setEdge(1, 5, 43);
    graph.setEdge(1, 6, 43);
    graph.setEdge(1, 7, 23);
    graph.setEdge(1, 8, 23);
    graph.setEdge(1, 9, 31);
    graph.setEdge(1, 10, 41);
    graph.setEdge(1, 11, 51);

    graph.setEdge(2, 0, 82);
    graph.setEdge(2, 1, 55);
    graph.setEdge(2, 3, 68);
    graph.setEdge(2, 4, 46);
    graph.setEdge(2, 5, 55);
    graph.setEdge(2, 6, 23);
    graph.setEdge(2, 7, 43);
    graph.setEdge(2, 8, 41);
    graph.setEdge(2, 9, 29);
    graph.setEdge(2, 10, 79);
    graph.setEdge(2, 11, 21);

    graph.setEdge(3, 0, 46);
    graph.setEdge(3, 1, 46);
    graph.setEdge(3, 2, 68);
    graph.setEdge(3, 4, 82);
    graph.setEdge(3, 5, 15);
    graph.setEdge(3, 6, 72);
    graph.setEdge(3, 7, 31);
    graph.setEdge(3, 8, 62);
    graph.setEdge(3, 9, 42);
    graph.setEdge(3, 10, 21);
    graph.setEdge(3, 11, 51);

    graph.setEdge(4, 0, 68);
    graph.setEdge(4, 1, 42);
    graph.setEdge(4, 2, 46);
    graph.setEdge(4, 3, 82);
    graph.setEdge(4, 5, 74);
    graph.setEdge(4, 6, 23);
    graph.setEdge(4, 7, 52);
    graph.setEdge(4, 8, 21);
    graph.setEdge(4, 9, 46);
    graph.setEdge(4, 10, 82);
    graph.setEdge(4, 11, 58);

    graph.setEdge(5, 0, 52);
    graph.setEdge(5, 1, 43);
    graph.setEdge(5, 2, 55);
    graph.setEdge(5, 3, 15);
    graph.setEdge(5, 4, 74);
    graph.setEdge(5, 6, 61);
    graph.setEdge(5, 7, 23);
    graph.setEdge(5, 8, 55);
    graph.setEdge(5, 9, 31);
    graph.setEdge(5, 10, 33);
    graph.setEdge(5, 11, 37);

    graph.setEdge(6, 0, 72);
    graph.setEdge(6, 1, 43);
    graph.setEdge(6, 2, 23);
    graph.setEdge(6, 3, 72);
    graph.setEdge(6, 4, 23);
    graph.setEdge(6, 5, 61);
    graph.setEdge(6, 7, 42);
    graph.setEdge(6, 8, 23);
    graph.setEdge(6, 9, 31);
    graph.setEdge(6, 10, 77);
    graph.setEdge(6, 11, 37);

    graph.setEdge(7, 0, 42);
    graph.setEdge(7, 1, 23);
    graph.setEdge(7, 2, 43);
    graph.setEdge(7, 3, 31);
    graph.setEdge(7, 4, 52);
    graph.setEdge(7, 5, 23);
    graph.setEdge(7, 6, 42);
    graph.setEdge(7, 8, 33);
    graph.setEdge(7, 9, 15);
    graph.setEdge(7, 10, 37);
    graph.setEdge(7, 11, 33);

    graph.setEdge(8, 0, 51);
    graph.setEdge(8, 1, 23);
    graph.setEdge(8, 2, 41);
    graph.setEdge(8, 3, 62);
    graph.setEdge(8, 4, 21);
    graph.setEdge(8, 5, 55);
    graph.setEdge(8, 6, 23);
    graph.setEdge(8, 7, 33);
    graph.setEdge(8, 9, 29);
    graph.setEdge(8, 10, 62);
    graph.setEdge(8, 11, 46);

    graph.setEdge(9, 0, 55);
    graph.setEdge(9, 1, 31);
    graph.setEdge(9, 2, 29);
    graph.setEdge(9, 3, 42);
    graph.setEdge(9, 4, 46);
    graph.setEdge(9, 5, 31);
    graph.setEdge(9, 6, 31);
    graph.setEdge(9, 7, 15);
    graph.setEdge(9, 8, 29);
    graph.setEdge(9, 10, 51);
    graph.setEdge(9, 11, 21);

    graph.setEdge(10, 0, 29);
    graph.setEdge(10, 1, 41);
    graph.setEdge(10, 2, 79);
    graph.setEdge(10, 3, 21);
    graph.setEdge(10, 4, 82);
    graph.setEdge(10, 5, 33);
    graph.setEdge(10, 6, 77);
    graph.setEdge(10, 7, 37);
    graph.setEdge(10, 8, 62);
    graph.setEdge(10, 9, 51);
    graph.setEdge(10, 11, 65);

    graph.setEdge(11, 0, 74);
    graph.setEdge(11, 1, 51);
    graph.setEdge(11, 2, 21);
    graph.setEdge(11, 3, 51);
    graph.setEdge(11, 4, 58);
    graph.setEdge(11, 5, 37);
    graph.setEdge(11, 6, 37);
    graph.setEdge(11, 7, 33);
    graph.setEdge(11, 8, 46);
    graph.setEdge(11, 9, 21);
    graph.setEdge(11, 10, 65);

    BruteForce tsp;
    tsp.solve(graph);

    ASSERT_EQ(264, tsp.getShortestPathLength());
    ASSERT_EQ("0 -> 1 -> 8 -> 4 -> 6 -> 2 -> 11 -> 9 -> 7 -> 5 -> 3 -> 10 -> 0", tsp.toString());
}
