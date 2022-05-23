#ifndef SDIZO_2_PRIM_H
#define SDIZO_2_PRIM_H

#include <string>
#include <algorithm>

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include "Heap.h"
#include "../graphs/AdjacencyList.h"
#include "../graphs/AdjacencyMatrix.h"

class Prim {
private:
    int* key;
    int* connection;
    int size;
public:
    void mst(AdjacencyList graph);

    void mst(AdjacencyMatrix graph);

    int getPathLen();

    int *getKey();

    int *getConnection();

    std::string toString();
};

#endif //SDIZO_2_PRIM_H
