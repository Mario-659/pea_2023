#include "gtest/gtest.h"

#include "graphs/AdjacencyMatrix.h"

TEST(MatrixGraph, shouldCopyAllEdges) {
    AdjacencyMatrix graph(6);
    graph.setEdge(0, 1, 5);
    graph.setEdge(0, 5, 2);
    graph.setEdge(1, 2, 3);
    graph.setEdge(1, 3, 1);
    graph.setEdge(2, 4, 3);
    graph.setEdge(3, 4, 3);
    graph.setEdge(3, 5, 1);
    graph.setEdge(4, 5, 4);
    graph.setEdge(1, 0, 5);
    graph.setEdge(5, 0, 2);
    graph.setEdge(2, 1, 3);
    graph.setEdge(3, 1, 1);
    graph.setEdge(4, 2, 3);
    graph.setEdge(4, 4, 3);
    graph.setEdge(5, 3, 1);
    graph.setEdge(5, 4, 4);

    AdjacencyMatrix copy = *graph.copy();

    for (int i=0; i<graph.getSize(); i++) {
        for (int j=0; j<graph.getSize(); j++) {
            ASSERT_EQ(graph.getEdgeWeight(i, j), copy.getEdgeWeight(i, j)) << "Error at: i=" << i << ", j=" << j;
        }
    }
}
