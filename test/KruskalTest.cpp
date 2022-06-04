#include "gtest/gtest.h"

#include "algorithms/Kruskal.h"

// picture of the graph in resources/
TEST(KruskalTest, shouldFindMSTFromMatrixCaseOne){
    AdjacencyMatrix graph(5);
    graph.addEdge(0, 1, 11);
    graph.addEdge(1, 2, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 3);
    graph.addEdge(2, 3, 22);
    graph.addEdge(3, 4, 9);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(20, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromListCaseOne){
    AdjacencyList graph(5);
    graph.addEdge(0, 1, 11);
    graph.addEdge(1, 2, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 3);
    graph.addEdge(2, 3, 22);
    graph.addEdge(3, 4, 9);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(20, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromListCaseTwo){
    AdjacencyList graph(6);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 4, 1);
    graph.addEdge(0, 5, 2);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(2, 3, 8);
    graph.addEdge(3, 4, 3);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 7);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(10, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromMatrixCaseTwo){
    AdjacencyMatrix graph(6);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 4, 1);
    graph.addEdge(0, 5, 2);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(2, 3, 8);
    graph.addEdge(3, 4, 3);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 7);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(10, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromListCaseThree){
    AdjacencyList graph(8);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 3, 9);
    graph.addEdge(0, 6, 3);
    graph.addEdge(1, 2, 9);
    graph.addEdge(1, 4, 8);
    graph.addEdge(1, 5, 6);
    graph.addEdge(1, 7, 7);
    graph.addEdge(2, 3, 9);
    graph.addEdge(2, 4, 4);
    graph.addEdge(2, 6, 5);
    graph.addEdge(2, 7, 3);
    graph.addEdge(3, 6, 8);
    graph.addEdge(4, 5, 2);
    graph.addEdge(4, 6, 1);
    graph.addEdge(5, 6, 5);
    graph.addEdge(6, 7, 9);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(26, kruskal.getPathLen());
}

TEST(KruskalTest, shouldFindMSTFromMatrixCaseThree){
    AdjacencyMatrix graph(8);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 3, 9);
    graph.addEdge(0, 6, 3);
    graph.addEdge(1, 2, 9);
    graph.addEdge(1, 4, 8);
    graph.addEdge(1, 5, 6);
    graph.addEdge(1, 7, 7);
    graph.addEdge(2, 3, 9);
    graph.addEdge(2, 4, 4);
    graph.addEdge(2, 6, 5);
    graph.addEdge(2, 7, 3);
    graph.addEdge(3, 6, 8);
    graph.addEdge(4, 5, 2);
    graph.addEdge(4, 6, 1);
    graph.addEdge(5, 6, 5);
    graph.addEdge(6, 7, 9);

    Kruskal kruskal;
    kruskal.mst(graph);

    ASSERT_EQ(26, kruskal.getPathLen());
}

