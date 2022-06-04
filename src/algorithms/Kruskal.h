#ifndef SDIZO_2_KRUSKAL_H
#define SDIZO_2_KRUSKAL_H

#include <iostream>
#include <string>

#include "Heap.h"
#include "LinkedList.h"
#include "../graphs/AdjacencyList.h"
#include "../graphs/AdjacencyMatrix.h"
#include "../graphs/Edge.h"
#include "MergeSort.h"


// Class representing subset
struct Subset {
    int parent;
    int rank;

    // Returns id of the subset element is in
    static int find(Subset* subsets, int element);

    // Joins subset containing u with subset containing v
    static void setUnion(Subset* subsets, int u, int v);
};

class Kruskal {
private:
    // linked list with edges for mst
    LinkedList<Edge> edgeList;

public:
    void mst(AdjacencyList graph);

    void mst(AdjacencyMatrix graph);

    LinkedList<Edge>* getEdgeList();

    void clear();

    int getPathLen();

    Kruskal();

    ~Kruskal();

    std::string toString();
};


#endif //SDIZO_2_KRUSKAL_H
