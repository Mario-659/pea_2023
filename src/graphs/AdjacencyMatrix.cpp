#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(int size) {
    this->size = size;
    int numberOfNodes = size * size;

    matrix = new int[numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        matrix[i] = NO_EDGE;
    }
}

AdjacencyMatrix::~AdjacencyMatrix() {
    delete[] matrix;
}

void AdjacencyMatrix::setEdge(int start, int end, int weight) {
    validateEdge(start, end);

    matrix[start*size + end] = weight;
}

int AdjacencyMatrix::getEdgeWeight(int start, int end) const {
    return matrix[start*size + end];
}

int AdjacencyMatrix::getSize() const {
    return size;
}

// TODO look at https://www.baeldung.com/cs/graphs-max-number-of-edges and adjust
void AdjacencyMatrix::generateRandomMatrix(int minWeight, int maxWeight) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDist(minWeight, maxWeight);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j) {
                setEdge(i, j, weightDist(gen));
            } else {
                setEdge(i, j, NO_EDGE);
            }
        }
    }
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

void AdjacencyMatrix::validateEdge(int start, int end) {
    if (start < 0 || start >= size || end < 0 || end >= size) {
        std::cout << "Invalid edge operation."
                     " Given params: start:" << start << " end:" << end <<
                     " matrix size:" << size << std::endl;

        exit(-1);
    }
}

AdjacencyMatrix *AdjacencyMatrix::copy() {
    auto copy = new AdjacencyMatrix(size);
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            copy->setEdge(i, j, matrix[i*size + j]);
        }
    }
    return copy;
}

