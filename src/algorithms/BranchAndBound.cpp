#include "BranchAndBound.h"
#include "Heap.h"

int BranchAndBound::TSPBound(AdjacencyMatrix &matrix, Node &u) {
    int currentPathCost = 0;

    // Calculate the current path cost based on the partial path in 'u'
    for (int i = 0; i < u.path.size() - 1; i++) {
        currentPathCost += matrix.getEdge(u.path[i], u.path[i + 1]);
    }

    std::vector<bool> visited(matrix.getSize(), false);
    // Mark visited nodes
    for (int node : u.path) {
        visited[node] = true;
    }

    // Sum the minimum outbound edge cost for each node to estimate the lower bound
    int estimatedRemainingCost = 0;
    for (int i = 0; i < matrix.getSize(); i++) {
        if (!visited[i] || i == u.path.back()) { // Only consider nodes that are unvisited or the last node in the path
            int minEdgeCost = std::numeric_limits<int>::max();
            for (int j = 0; j < matrix.getSize(); j++) {
                if (i != j && matrix.getEdge(i, j) != -1) { // Ensure no self-loops and no missing edges
                    minEdgeCost = std::min(minEdgeCost, matrix.getEdge(i, j));
                }
            }
            // Add the minimum edge cost for node 'i' to the remaining estimated cost
            if (minEdgeCost != std::numeric_limits<int>::max()) {
                estimatedRemainingCost += minEdgeCost;
            }
        }
    }

    // Total bound = current path cost + estimated remaining minimum cost
    return currentPathCost + estimatedRemainingCost;
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
