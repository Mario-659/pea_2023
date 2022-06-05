#ifndef SDIZO_2_ADJACENCYMATRIX_H
#define SDIZO_2_ADJACENCYMATRIX_H

#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>

#define NO_EDGE INT_MAX

/**
 * Undirected graph representation as matrix
 */
class AdjacencyMatrix {
public:
    // Constructor for graph
    AdjacencyMatrix(int size);

    // Adds new undirected edge to the graph
    void addUndEdge(int start, int end, int weight);

    // Adds new directed edge to the graph
    void addEdge(int start, int end, int weight);

    // Removes edge from the graph
    void removeEdge(int start, int end);

    // Returns size
    int getSize();

    // Returns string representation
    std::string toString();

    // Returns weight of given edge
    int getEdge(int start, int end);

    ~AdjacencyMatrix();
private:
    int size;
    int* matrix;

    bool validateEdge(int start, int end);
};

#endif //SDIZO_2_ADJACENCYMATRIX_H
