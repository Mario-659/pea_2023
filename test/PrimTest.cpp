#include "gtest/gtest.h"

#include "algorithms/Prim.h"

// picture of the graph in resources/

TEST(PrimTest, shouldFindMSTFromMatrixCaseOne){
    AdjacencyMatrix graph(5);
    graph.addEdge(0, 1, 11);
    graph.addEdge(1, 2, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 3);
    graph.addEdge(2, 3, 22);
    graph.addEdge(3, 4, 9);

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(20, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromListCaseOne){
    AdjacencyList graph(5);
    graph.addEdge(0, 1, 11);
    graph.addEdge(1, 2, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 3);
    graph.addEdge(2, 3, 22);
    graph.addEdge(3, 4, 9);

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(20, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromListCaseTwo){
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

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(10, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromMatrixCaseTwo){
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

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(10, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromListCaseThree){
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

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(26, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromMatrixCaseThree){
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

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(26, prim.getPathLen());
}

