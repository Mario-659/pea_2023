#include "Greedy.h"

void Greedy::solve(AdjacencyMatrix &graph, int startingVertex) {
    int verticesNumber = graph.getSize();
    std::vector<bool> visited(verticesNumber, false);
    path.clear();
    shortestPathLength = 0;

    // Start at the given starting vertex
    int currentVertex = startingVertex;
    path.push_back(currentVertex);
    visited[currentVertex] = true;

    for (int i = 1; i < verticesNumber; ++i) {
        int nearestNeighbor = -1;
        int minWeight = std::numeric_limits<int>::max();

        // Find the nearest unvisited neighbor
        for (int j = 0; j < verticesNumber; ++j) {
            if (!visited[j] && graph.getEdgeWeight(currentVertex, j) < minWeight) {
                minWeight = graph.getEdgeWeight(currentVertex, j);
                nearestNeighbor = j;
            }
        }

        if (nearestNeighbor == -1) {
//            std::cerr << "Error: Unable to find a valid neighbor. Check the graph input." << std::endl;
            return;
        }

        // Move to the nearest neighbor
        visited[nearestNeighbor] = true;
        path.push_back(nearestNeighbor);
        shortestPathLength += minWeight;
        currentVertex = nearestNeighbor;
    }

    // Return to the starting vertex to complete the cycle
    shortestPathLength += graph.getEdgeWeight(currentVertex, startingVertex);
    path.push_back(startingVertex);
}


void Greedy::solve(AdjacencyMatrix &graph) {
    int verticesNumber = graph.getSize();
    int globalBestCost = std::numeric_limits<int>::max();
    std::vector<int> globalBestPath;

    for (int startingVertex = 0; startingVertex < verticesNumber; ++startingVertex) {
        // Reset the state for each starting vertex
        std::vector<bool> visited(verticesNumber, false);
        std::vector<int> currentPath;
        int currentCost = 0;

        // Start from the current starting vertex
        int currentVertex = startingVertex;
        currentPath.push_back(currentVertex);
        visited[currentVertex] = true;

        // Greedy algorithm to construct a tour
        for (int i = 1; i < verticesNumber; ++i) {
            int nearestNeighbor = -1;
            int minWeight = std::numeric_limits<int>::max();

            // Find the nearest unvisited neighbor
            for (int j = 0; j < verticesNumber; ++j) {
                if (!visited[j] && graph.getEdgeWeight(currentVertex, j) < minWeight) {
                    minWeight = graph.getEdgeWeight(currentVertex, j);
                    nearestNeighbor = j;
                }
            }

            if (nearestNeighbor == -1) {
                std::cerr << "Error: Unable to find a valid neighbor. Check the graph input." << std::endl;
                return;
            }

            // Move to the nearest neighbor
            visited[nearestNeighbor] = true;
            currentPath.push_back(nearestNeighbor);
            currentCost += minWeight;
            currentVertex = nearestNeighbor;
        }

        // Return to the starting vertex to complete the cycle
        currentCost += graph.getEdgeWeight(currentVertex, startingVertex);
        currentPath.push_back(startingVertex);

        // Check if the current path is the best so far
        if (currentCost < globalBestCost) {
            globalBestCost = currentCost;
            globalBestPath = currentPath;
        }
    }

    // Update the class attributes with the best solution found
    shortestPathLength = globalBestCost;
    path = globalBestPath;
}


std::string Greedy::toString() {
    std::string result;
    for (int city : path) {
        result += std::to_string(city) + " -> ";
    }
    return result;
}

