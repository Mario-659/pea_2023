#include "gtest/gtest.h"

#include "algorithms/Kruskal.h"

// picture of the graph in resources/
TEST(KruskalTest, shouldFindMSTFromMatrixCaseOne){
    AdjacencyMatrix graph(5);
    graph.addUndEdge(0, 1, 11);
    graph.addUndEdge(1, 2, 5);
    graph.addUndEdge(0, 2, 3);
    graph.addUndEdge(1, 3, 3);
    graph.addUndEdge(2, 3, 22);
    graph.addUndEdge(3, 4, 9);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(20, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromListCaseOne){
    AdjacencyList graph(5);
    graph.addUndEdge(0, 1, 11);
    graph.addUndEdge(1, 2, 5);
    graph.addUndEdge(0, 2, 3);
    graph.addUndEdge(1, 3, 3);
    graph.addUndEdge(2, 3, 22);
    graph.addUndEdge(3, 4, 9);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(20, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromListCaseTwo){
    AdjacencyList graph(6);
    graph.addUndEdge(0, 1, 4);
    graph.addUndEdge(0, 4, 1);
    graph.addUndEdge(0, 5, 2);
    graph.addUndEdge(1, 2, 2);
    graph.addUndEdge(1, 4, 2);
    graph.addUndEdge(2, 3, 8);
    graph.addUndEdge(3, 4, 3);
    graph.addUndEdge(3, 5, 6);
    graph.addUndEdge(4, 5, 7);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(10, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromMatrixCaseTwo){
    AdjacencyMatrix graph(6);
    graph.addUndEdge(0, 1, 4);
    graph.addUndEdge(0, 4, 1);
    graph.addUndEdge(0, 5, 2);
    graph.addUndEdge(1, 2, 2);
    graph.addUndEdge(1, 4, 2);
    graph.addUndEdge(2, 3, 8);
    graph.addUndEdge(3, 4, 3);
    graph.addUndEdge(3, 5, 6);
    graph.addUndEdge(4, 5, 7);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(10, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromListCaseThree){
    AdjacencyList graph(8);
    graph.addUndEdge(0, 1, 5);
    graph.addUndEdge(0, 3, 9);
    graph.addUndEdge(0, 6, 3);
    graph.addUndEdge(1, 2, 9);
    graph.addUndEdge(1, 4, 8);
    graph.addUndEdge(1, 5, 6);
    graph.addUndEdge(1, 7, 7);
    graph.addUndEdge(2, 3, 9);
    graph.addUndEdge(2, 4, 4);
    graph.addUndEdge(2, 6, 5);
    graph.addUndEdge(2, 7, 3);
    graph.addUndEdge(3, 6, 8);
    graph.addUndEdge(4, 5, 2);
    graph.addUndEdge(4, 6, 1);
    graph.addUndEdge(5, 6, 5);
    graph.addUndEdge(6, 7, 9);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(26, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromMatrixCaseThree){
    AdjacencyMatrix graph(8);
    graph.addUndEdge(0, 1, 5);
    graph.addUndEdge(0, 3, 9);
    graph.addUndEdge(0, 6, 3);
    graph.addUndEdge(1, 2, 9);
    graph.addUndEdge(1, 4, 8);
    graph.addUndEdge(1, 5, 6);
    graph.addUndEdge(1, 7, 7);
    graph.addUndEdge(2, 3, 9);
    graph.addUndEdge(2, 4, 4);
    graph.addUndEdge(2, 6, 5);
    graph.addUndEdge(2, 7, 3);
    graph.addUndEdge(3, 6, 8);
    graph.addUndEdge(4, 5, 2);
    graph.addUndEdge(4, 6, 1);
    graph.addUndEdge(5, 6, 5);
    graph.addUndEdge(6, 7, 9);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(26, kruskal.getPathLen());
}

