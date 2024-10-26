#include "BranchAndBound.h"
#include "Heap.h"

/**
 * Calculate the lower bound for TSP using the current path and remaining nodes.
 */
int BranchAndBound::TSPBound(AdjacencyMatrix &matrix, Node &u) {
    int currentPathCost = 0;

    // add the cost of edges in the current path
    for (int i = 0; i < u.path.size() - 1; i++) {
        currentPathCost += matrix.getEdge(u.path[i], u.path[i + 1]);
    }

    std::vector<bool> visited(matrix.getSize(), false);
    // mark visited nodes
    for (int node : u.path) {
        visited[node] = true;
    }

    // Add minimum edge costs for unvisited nodes
    int minEdge = 0;
    for (int i = 0; i < matrix.getSize(); i++) {
        if (!visited[i]) {
            // Find the minimum edge connected to the unvisited node
            int minCost = std::numeric_limits<int>::max();
            for (int j = 0; j < matrix.getSize(); j++) {
                if (i != j && !visited[j]) {
                    int edgeWeight = matrix.getEdge(i, j);
                    if (edgeWeight < minCost) {
                        minCost = edgeWeight;
                    }
                }
            }
            // If we found a valid edge, add it to the bound
            if (minCost != std::numeric_limits<int>::max()) {
                minEdge += minCost;
            }
        }
    }

    // To complete the bound, add the minimum edge for the return path
    int returnMin = std::numeric_limits<int>::max();
    for (int i = 0; i < matrix.getSize(); i++) {
        if (i != u.path[0] && !visited[i]) { // Return to the starting node
            int edgeWeight = matrix.getEdge(u.path.back(), i);
            if (edgeWeight < returnMin) {
                returnMin = edgeWeight;
            }
        }
    }

    // If we found a valid return path, add it
    if (returnMin != std::numeric_limits<int>::max()) {
        minEdge += returnMin;
    }

    // The total bound is the currentPathCost of the current path plus the minimum edge costs
    return currentPathCost + minEdge;
}


void BranchAndBound::findPath(AdjacencyMatrix &graph) {
    Heap<Node> nodes(size * size);

    Node start;
    start.level = 0;
    start.path.push_back(0);
    start.bound = TSPBound(graph, start);

    nodes.push(start);

    while (nodes.getSize() > 0) {
        Node curr = nodes.extractMin();

        if (curr.bound < minCost) {
            for (int i = 1; i < size; i++) {
                if (std::find(curr.path.begin(), curr.path.end(), i) == curr.path.end()) {
                    Node child = curr;
                    child.path.push_back(i);
                    child.level = curr.level + 1;

                    if (child.level == size - 1) {
                        child.path.push_back(0);
                        int currCost = 0;
                        for (size_t j = 0; j < child.path.size() - 1; j++) {
                            currCost += graph.getEdge(child.path[j], child.path[j + 1]);
                        }
                        if (currCost < minCost) {
                            minCost = currCost;
                            bestPath = child.path;
                        }
                    } else {
                        child.bound = TSPBound(graph, child);
                        if (child.bound < minCost) {
                            nodes.push(child);
                        }
                    }
                }
            }
        }
    }
}

void BranchAndBound::solve(AdjacencyMatrix &graph) {
    size = graph.getSize();
    findPath(graph);
}

std::string BranchAndBound::toString() {
    std::string path;
    for (size_t i = 0; i < bestPath.size() - 1; i++) {
        path += std::to_string(bestPath[i]) + " -> ";
    }
    return path + std::to_string(bestPath.back());
}
