#ifndef PEA_ADJACENCYMATRIX_H
#define PEA_ADJACENCYMATRIX_H

#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <random>

#define NO_EDGE 1222

/**
 * Graph representation as matrix
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
    int getSize() const;

    AdjacencyMatrix* copy();

    // Returns string representation
    std::string toString();

    // Returns weight of given edge
    int getEdge(int start, int end) const;

    void generateRandomMatrix(int minWeight, int maxWeight);

    ~AdjacencyMatrix();
private:
    int size;
    int* matrix;

    bool validateEdge(int start, int end);
};

#endif //PEA_ADJACENCYMATRIX_H
