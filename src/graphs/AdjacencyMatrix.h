#ifndef PEA_ADJACENCYMATRIX_H
#define PEA_ADJACENCYMATRIX_H

#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <random>

#define NO_EDGE 1220

/**
 * Graph representation as matrix
 */
class AdjacencyMatrix {
public:
    // init matrix wih no edges defined
    AdjacencyMatrix(int size);
    void setEdge(int start, int end, int weight);
    int getEdgeWeight(int start, int end) const;
    int getSize() const;
    void generateRandomMatrix(int minWeight, int maxWeight);
    AdjacencyMatrix* copy();
    std::string toString();
    ~AdjacencyMatrix();
private:
    int size;
    int* matrix;

    void validateEdge(int start, int end);
};

#endif //PEA_ADJACENCYMATRIX_H
