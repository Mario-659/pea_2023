#include "gtest/gtest.h"

#include "algorithms/Prim.h"

// picture of the graph in resources/

TEST(PrimTest, shouldFindMSTFromMatrixCaseOne){
    AdjacencyMatrix graph(5);
    graph.addUndEdge(0, 1, 11);
    graph.addUndEdge(1, 2, 5);
    graph.addUndEdge(0, 2, 3);
    graph.addUndEdge(1, 3, 3);
    graph.addUndEdge(2, 3, 22);
    graph.addUndEdge(3, 4, 9);

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(20, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromListCaseOne){
    AdjacencyList graph(5);
    graph.addUndEdge(0, 1, 11);
    graph.addUndEdge(1, 2, 5);
    graph.addUndEdge(0, 2, 3);
    graph.addUndEdge(1, 3, 3);
    graph.addUndEdge(2, 3, 22);
    graph.addUndEdge(3, 4, 9);

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(20, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromListCaseTwo){
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

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(10, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromMatrixCaseTwo){
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

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(10, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromListCaseThree){
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

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(26, prim.getPathLen());
}

TEST(PrimTest, shouldFindMSTFromMatrixCaseThree){
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

    Prim prim;
    prim.mst(graph);

    ASSERT_EQ(26, prim.getPathLen());
}

