#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(int size) {
    this->size = size;

    matrix = new int[size*size];
    for (int i=0; i<size*size; i++) {
        matrix[i] = NO_EDGE;
    }
}

AdjacencyMatrix::~AdjacencyMatrix() {
//    delete matrix;
}

void AdjacencyMatrix::addUndEdge(int start, int end, int weight) {
    if (!validateEdge(start, end)) return;

    matrix[start*size + end] = weight;
    matrix[end*size + start] = weight;
}

void AdjacencyMatrix::addEdge(int start, int end, int weight) {
    if (!validateEdge(start, end)) return;

    matrix[start*size + end] = weight;
}

void AdjacencyMatrix::removeEdge(int start, int end) {
    if (!validateEdge(start, end)) return;

    matrix[start*size + end] = NO_EDGE;
}

int AdjacencyMatrix::getEdge(int start, int end) {
    return matrix[start*size + end];
}

int AdjacencyMatrix::getSize() {
    return size;
}

std::string AdjacencyMatrix::toString() {
    std::ostringstream oss;

    // find the largest num
    int largest = 0;
    for (int i=0; i<size*size; i++) {
        if(matrix[i] > largest && matrix[i] != NO_EDGE) largest = matrix[i];
    }

    // get length of the largest num
    int maxWidth = 1;
    while(largest != 0) {
        maxWidth++;
        largest /= 10;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int value = matrix[i*size + j];
            if(value == NO_EDGE) value = 0;
            oss << std::setw(maxWidth) << value << ' ';
        }
        oss << "\n";
    }
    std::string output = oss.str();
    return output;
}

bool AdjacencyMatrix::validateEdge(int start, int end) {
    if (start < 0 || start >= size || end < 0 || end >= size) {
        std::cout << "Invalid edge operation."
                     " Given params: start:" << start << " end:" << end <<
                     " matrix size:" << size << std::endl;
        return false;
    }
    return true;
}

