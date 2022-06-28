#include "gtest/gtest.h"

#include "graphs/AdjacencyList.h"
#include "graphs/AdjacencyMatrix.h"

TEST(ListGraph, shouldCopyAllEdges) {
    AdjacencyList graph(6);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 5, 2);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 4, 3);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 5, 4);
    graph.addEdge(1, 0, 5);
    graph.addEdge(5, 0, 2);
    graph.addEdge(2, 1, 3);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 2, 3);
    graph.addEdge(4, 4, 3);
    graph.addEdge(5, 3, 1);
    graph.addEdge(5, 4, 4);

    AdjacencyList copy = *graph.copy();

    for (int i=0; i<graph.getSize(); i++) {
        for (int j=0; j<graph.getSize(); j++) {
            ASSERT_EQ(graph.getEdge(i, j), copy.getEdge(i, j)) << "Error at: i=" << i << ", j=" << j;
        }
    }
}

TEST(MatrixGraph, shouldCopyAllEdges) {
    AdjacencyMatrix graph(6);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 5, 2);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 4, 3);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 5, 4);
    graph.addEdge(1, 0, 5);
    graph.addEdge(5, 0, 2);
    graph.addEdge(2, 1, 3);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 2, 3);
    graph.addEdge(4, 4, 3);
    graph.addEdge(5, 3, 1);
    graph.addEdge(5, 4, 4);

    AdjacencyMatrix copy = *graph.copy();

    for (int i=0; i<graph.getSize(); i++) {
        for (int j=0; j<graph.getSize(); j++) {
            ASSERT_EQ(graph.getEdge(i, j), copy.getEdge(i, j)) << "Error at: i=" << i << ", j=" << j;
        }
    }
}
