#include "gtest/gtest.h"

#include "algorithms/Dijkstra.h"


// dane_droga_sk1.txt
TEST(DijkstraTest, shouldFindPathFromMatrixCaseOne) {
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

    Dijkstra dijkstra;
    dijkstra.shortestPath(graph, 0);

    ASSERT_EQ(0, dijkstra.getPathLen(0));
    ASSERT_EQ(4, dijkstra.getPathLen(1));
    ASSERT_EQ(7, dijkstra.getPathLen(2));
    ASSERT_EQ(3, dijkstra.getPathLen(3));
    ASSERT_EQ(6, dijkstra.getPathLen(4));
    ASSERT_EQ(2, dijkstra.getPathLen(5));
}

TEST(DijkstraTest, shouldFindPathFromListCaseOne){
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

    Dijkstra dijkstra;
    dijkstra.shortestPath(graph, 0);

    ASSERT_EQ(0, dijkstra.getPathLen(0));
    ASSERT_EQ(4, dijkstra.getPathLen(1));
    ASSERT_EQ(7, dijkstra.getPathLen(2));
    ASSERT_EQ(3, dijkstra.getPathLen(3));
    ASSERT_EQ(6, dijkstra.getPathLen(4));
    ASSERT_EQ(2, dijkstra.getPathLen(5));
}

// dane_droga_sk2.txt
TEST(DijkstraTest, shouldFindPathFromMatrixCaseTwo){
    AdjacencyMatrix graph(6);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 5);
    graph.addEdge(0, 3, 9);
    graph.addEdge(1, 0, 3);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 4);
    graph.addEdge(1, 4, 7);
    graph.addEdge(2, 0, 5);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 4, 6);
    graph.addEdge(2, 5, 8);
    graph.addEdge(3, 0, 9);
    graph.addEdge(3, 1, 4);
    graph.addEdge(3, 2, 2);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 1, 2);
    graph.addEdge(4, 2, 6);
    graph.addEdge(4, 3, 2);
    graph.addEdge(4, 5, 5);
    graph.addEdge(5, 2, 8);
    graph.addEdge(5, 3, 2);
    graph.addEdge(5, 4, 5);

    Dijkstra dijkstra;
    dijkstra.shortestPath(graph, 0);

    ASSERT_EQ(0, dijkstra.getPathLen(0));
    ASSERT_EQ(3, dijkstra.getPathLen(1));
    ASSERT_EQ(5, dijkstra.getPathLen(2));
    ASSERT_EQ(7, dijkstra.getPathLen(3));
    ASSERT_EQ(9, dijkstra.getPathLen(4));
    ASSERT_EQ(9, dijkstra.getPathLen(5));
}

TEST(DijkstraTest, shouldFindPathFromListCaseTwo){
    AdjacencyList graph(6);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 5);
    graph.addEdge(0, 3, 9);
    graph.addEdge(1, 0, 3);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 4);
    graph.addEdge(1, 4, 7);
    graph.addEdge(2, 0, 5);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 4, 6);
    graph.addEdge(2, 5, 8);
    graph.addEdge(3, 0, 9);
    graph.addEdge(3, 1, 4);
    graph.addEdge(3, 2, 2);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 1, 2);
    graph.addEdge(4, 2, 6);
    graph.addEdge(4, 3, 2);
    graph.addEdge(4, 5, 5);
    graph.addEdge(5, 2, 8);
    graph.addEdge(5, 3, 2);
    graph.addEdge(5, 4, 5);

    Dijkstra dijkstra;
    dijkstra.shortestPath(graph, 0);

    ASSERT_EQ(0, dijkstra.getPathLen(0));
    ASSERT_EQ(3, dijkstra.getPathLen(1));
    ASSERT_EQ(5, dijkstra.getPathLen(2));
    ASSERT_EQ(7, dijkstra.getPathLen(3));
    ASSERT_EQ(9, dijkstra.getPathLen(4));
    ASSERT_EQ(9, dijkstra.getPathLen(5));
}