#include "BellmanFord.h"

void BellmanFord::shortestPath(AdjacencyMatrix graph, int start) {
    size = graph.getSize();
    connections = new int[size];
    weights = new int[size];
    this->start = start;

    // fill weights with INT_MAX and connections as undefined
    for (int i = 0; i < size; i++) {
        weights[i] = INT_MAX;
        connections[i] = -1;
    }

    weights[start] = 0;

    for (int i = 0; i < size; i++) {
        // edge relaxation for every edge
        for (int u = 0; u < size; u++) {
            for (int v = 0; v < size; v++) {
                int weight = graph.getEdge(u, v);
                if (weight != INT_MAX && weights[u] + weight < weights[v] && weights[u] != INT_MAX) {
                    weights[v] = weights[u] + weight;
                    connections[v] = u;
                }
            }
        }
    }
}

void BellmanFord::shortestPath(AdjacencyList graph, int start) {
    size = graph.getSize();
    connections = new int[size];
    weights = new int[size];
    this->start = start;

    for (int i = 0; i < size; i++) {
        weights[i] = INT_MAX;
        connections[i] = -1;
    }

    weights[start] = 0;

    for (int i = 0; i < size; i++) {
        for (int u = 0; u < size; u++) {
            auto node = graph.getVertexNeighbours(u)->getHeadNode();
            while (node != nullptr) {
                ListNode item = node->data;
                if (weights[u] + item.weight < weights[item.index] && weights[u] != INT_MAX) {
                    weights[item.index] = weights[u] + item.weight;
                    connections[item.index] = u;
                }
                node = node->next;
            }
        }
    }
}

int *BellmanFord::getWeights() {
    return weights;
}

int *BellmanFord::getPredeccesorArray() {
    return connections;
}

int BellmanFord::getPathLen(int end) {
    if (end < 0 || end >= size)
        return INT_MAX;

    return weights[end];
}

std::string BellmanFord::toString() {
    std::string text;
    std::string path;

    for (int i = 0; i < size; i++) {
        if (weights[i] == INT_MAX) continue;
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
                    + std::to_string(weights[i]) + "): ");
        text.append("Path to vertex: " + path + "\n");
        path.clear();
    }
    return text;
}

BellmanFord::BellmanFord() = default;

BellmanFord::~BellmanFord() {
    delete[] weights;
    delete[] connections;
}
