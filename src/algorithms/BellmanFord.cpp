#include "BellmanFord.h"

void BellmanFord::shortestPath(AdjacencyMatrix graph, int start) {
    size = graph.getSize();
    connections = new int[size];
    p = new int[size];
    this->start = start;

    // fill p with INT_MAX and connections as undefined
    for (int i = 0; i < size; i++) {
        p[i] = INT_MAX;
        connections[i] = -1;
    }

    p[start] = 0;

    for (int i = 0; i < size; i++) {
        // edge relaxation for every edge
        for (int u = 0; u < size; u++) {
            for (int v = 0; v < size; v++) {
                int weight = graph.getEdge(u, v);
                if (weight != INT_MAX && p[u] + weight < p[v] && p[u] != INT_MAX) {
                    p[v] = p[u] + weight;
                    connections[v] = u;
                }
            }
        }
    }
}

void BellmanFord::shortestPath(AdjacencyList graph, int start) {
    size = graph.getSize();
    connections = new int[size];
    p = new int[size];
    this->start = start;

    for (int i = 0; i < size; i++) {
        p[i] = INT_MAX;
        connections[i] = -1;
    }

    p[start] = 0;

    for (int i = 0; i < size; i++) {
        for (int u = 0; u < size; u++) {
            auto node = graph.getVertexNeighbours(u)->getHeadNode();
            while (node != nullptr) {
                ListNode item = node->data;
                if (p[u] + item.weight < p[item.index] && p[u] != INT_MAX) {
                    p[item.index] = p[u] + item.weight;
                    connections[item.index] = u;
                }
                node = node->next;
            }
        }
    }
}

int *BellmanFord::getWeights() {
    return p;
}

int *BellmanFord::getPredeccesorArray() {
    return connections;
}

int BellmanFord::getPathLen(int end) {
    if (end < 0 || end >= size)
        return INT_MAX;

    return p[end];
}

std::string BellmanFord::toString() {
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

BellmanFord::BellmanFord() = default;

BellmanFord::~BellmanFord() {
//    delete[] p;
//    delete[] connections;
}
