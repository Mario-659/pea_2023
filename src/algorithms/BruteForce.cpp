#include "BruteForce.h"

void BruteForce::findShortestPath(AdjacencyMatrix &graph) {
    shortestPathLength = std::numeric_limits<int>::max();

    size = graph.getSize();
    // initialize the list of vertices. Start from 1 since 0 is the starting vertex.
    std::vector<int> vertices;
    for (int i = 1; i < size; i++) {
        vertices.push_back(i);
    }

    do {
        int currentPathWeight = 0;
        bool routeDoesNotExist = false;
        int lastVertex = 0;  // start at vertex 0

        // calculate the current path weight
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

        // add weight of returning to the starting vertex
        int returnEdgeWeight = graph.getEdge(lastVertex, 0);
        if (returnEdgeWeight == NO_EDGE) {
            continue;
        }
        currentPathWeight += returnEdgeWeight;

        // update the shortest path if current path is shorter
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
