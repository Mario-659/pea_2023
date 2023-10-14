#include "BruteForce.h"

void BruteForce::findShortestPath(AdjacencyMatrix &graph) {
    size = graph.getSize();
    std::vector<int> vertices;
    shortestPathLength = INT_MAX;

    // Initialize the list of vertices. Start from 1 since 0 is the starting vertex.
    for (int i = 1; i < size; i++) {
        vertices.push_back(i);
    }

    do {
        int currentPathWeight = 0;
        bool routeDoesNotExist = false;
        int lastVertex = 0;  // Start at vertex 0

        // Calculate the current path weight
        for (int vertex : vertices) {
            int edgeWeight = graph.getEdge(lastVertex, vertex);

            if (edgeWeight == NO_EDGE) {
                routeDoesNotExist = true;
                break;
            }

            currentPathWeight += edgeWeight;
            lastVertex = vertex;
        }

        if (routeDoesNotExist) {
            continue;
        }

        // Add weight of returning to the starting vertex
        int returnEdgeWeight = graph.getEdge(lastVertex, 0);
        if (returnEdgeWeight == NO_EDGE) {
            continue;
        }
        currentPathWeight += returnEdgeWeight;

        // Update the shortest path if current path is shorter
        if (currentPathWeight < shortestPathLength) {
            shortestPathLength = currentPathWeight;
            bestPath = vertices;
        }

    } while (std::next_permutation(vertices.begin(), vertices.end()));
}

std::string BruteForce::toString() {
    std::string path = "0 -> ";
    for (int i : bestPath) {
        path += std::to_string(i) + " -> ";
    }
    path += "0";
    return path;
}
