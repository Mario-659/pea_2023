#include "Prim.h"

void Prim::mst(AdjacencyList graph) {
    // allocating memory
    size = graph.getSize();
    Heap<ListNode> queue(size);
    key = new int[size];
    connection = new int[size];

    for (int i = 0; i < size; i++) {
        key[i] = INT_MAX;
    }

    // random starting vertex
    int startingV = rand() % size;
    key[startingV] = 0;
    connection[startingV] = -1;

    // filling priority que
    for (int i = 0; i < size; i++)
        queue.push({key[i], i });

    // for every vertex
    while (queue.getSize() != 0) {
        auto item = queue.extractMin();
        // for every neighbour of vertex
        for (auto edge : graph.getVertexNeighbours(item.index)) {
            int v = edge.index;
            if (queue.contains({key[v], v }) && edge.weight < key[v]) {
                // update solution mst with better path
                queue.update({key[v], v }, {edge.weight, v });
                key[v] = edge.weight;
                connection[v] = item.index;
            }
        }
    }
}

void Prim::mst(AdjacencyMatrix graph) {
    // allocating memory
    size = graph.getSize();
    key = new int[size];
    connection = new int[size];
    Heap<ListNode> queue(size);

    for (int i = 0; i < size; i++)
        key[i] = INT_MAX;

    // random starting point
    int startingV = rand() % size;
    key[startingV] = 0;
    connection[startingV] = -1;

    for (int i = 0; i < size; i++)
        queue.push({key[i], i });

    while (queue.getSize() != 0) {
        auto item = queue.extractMin();
        // for every neighbour of vertex
        for (int i = 0; i < size; i++) {
            int weight = graph.getEdge(item.index, i);
            if (weight != NO_EDGE) {
                // if found better path
                if (queue.contains({key[i], i  }) && weight < key[i]) {
                    queue.update({key[i], i  }, {weight, i });
                    key[i] = weight;
                    connection[i] = item.index;
                }
            }
        }
    }
}

std::string Prim::toString() {
    std::string text("Edges in MST: \n");

    for (int i = 0; i < size; i++) {
        if (connection[i] != -1) {
            int weight = key[i];
            if (weight == NO_EDGE) weight = 0;
            text += std::to_string(i);
            text += ", ";
            text += std::to_string(connection[i]);
            text += ", weight ";
            text += std::to_string(weight);
            text += "\n";
        }
    }
    text += "Weight of the tree: ";
    text += std::to_string(getPathLen());
    text += "\n";
    return text;
}

int Prim::getPathLen() {
    int len = 0;
    for (int i = 0; i < size; i++) {
        if (connection[i] != -1)
            len += key[i];
    }
    return len;
}

int *Prim::getKey() {
    return key;
}

int *Prim::getConnection() {
    return connection;
}
