#include "Dijkstra.h"

Dijkstra::Dijkstra() = default;

Dijkstra::~Dijkstra() {
//    delete[] p;
//    delete[] connections;
}

void Dijkstra::shortestPath(AdjacencyMatrix graph, int start) {
    size = graph.getSize();
    p = new int[size];
    connections = new int[size];
    this->start = start;

    Heap<ListNode> queue(size);

    // fill p with INT_MAX and connections as undefined
    for (int i = 0; i < size; i++) {
        p[i] = INT_MAX;
        connections[i] = -1;
    }



    p[start] = 0;

    // fill priority queue
    for (int i = 0; i < size; i++)
        queue.push({p[i], i});

    // for every vertex
    while (queue.getSize() != 0) {
        auto item = queue.extractMin();
        // for every neighbour do edge relaxation (https://www.baeldung.com/cs/dijkstra-edge-relaxation)
        for (int i = 0; i < size; i++) {
            int weight = graph.getEdge(item.index, i);
            if (weight != INT_MAX && p[item.index] + weight < p[i] && p[item.index] != INT_MAX) {
                ListNode updateItem = {p[i], i };
                p[i] = p[item.index] + weight;
                connections[i] = item.index;
                queue.update(updateItem, {p[i], i});
            }
        }
    }
}

void Dijkstra::shortestPath(AdjacencyList graph, int start) {
    size = graph.getSize();
    p = new int[size];
    connections = new int[size];
    this->start = start;

    Heap<ListNode> queue(size);

    for (int i = 0; i < size; i++) {
        p[i] = INT_MAX;
        connections[i] = -1;
    }

    p[start] = 0;
    for (int i = 0; i < size; i++)
        queue.push({p[i], i});


    while (queue.getSize() != 0) {
        auto item = queue.extractMin();
        for (int i = 0; i < size; i++) {
            int weight = graph.getEdge(item.index, i);
            if (weight != INT_MAX) {
                if (p[item.index] + weight < p[i] && p[item.index] != INT_MAX) {
                    ListNode updateItem = {p[i], i  };
                    p[i] = p[item.index] + weight;
                    connections[i] = item.index;
                    queue.update(updateItem, {p[i], i});
                }
            }
        }
    }
}

int* Dijkstra::getPredeccesorArray() {
    return connections;
}

int* Dijkstra::getWeights() {
    return p;
}

int Dijkstra::getPathLen(int end) {
    if (end < 0 || end >= size)
        return INT_MAX;

    return p[end];
}

std::string Dijkstra::toString() {
    std::string text;
    std::string path;

    for (int i = 0; i < size; i++) {
        if (p[i] == INT_MAX) continue;
        int v = i;
        while (v != start) {
            path.insert(0, std::to_string(connections[v]) + " -> ");
            v = connections[v];
        }
        path.append(std::to_string(i));
        text.append(std::to_string(start)
                    + " -> "
                    + std::to_string(i)
                    + " (weight="
                    + std::to_string(p[i]) + "): ");
        text.append("Path to vertex: " + path + "\n");
        path.clear();
    }
    return text;
}
