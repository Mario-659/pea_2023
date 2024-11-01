#include "BranchAndBound.h"

#include <climits>
#include <algorithm>

BranchAndBound::BranchAndBound() : TSPSolver(), minCost(INT_MAX) {}

// Calculate the lower bound of a path starting at the given node
int BranchAndBound::calculateBound(const AdjacencyMatrix &graph, const Node &node) {
    int bound = node.pathCost;
    int size = graph.getSize();

    // Add minimum outgoing edge costs for unvisited nodes
    for (int i = 0; i < size; i++) {
        if (!node.visited[i]) {
            int minEdge = INT_MAX;
            for (int j = 0; j < size; j++) {
                if (i != j && !node.visited[j]) {
                    minEdge = std::min(minEdge, graph.getEdgeWeight(i, j));
                }
            }
            bound += (minEdge == INT_MAX) ? 0 : minEdge;
        }
    }

    return bound;
}

// Main function to solve the ATSP using branch-and-bound
void BranchAndBound::solveATSP(const AdjacencyMatrix &graph) {
    int size = graph.getSize();
    std::priority_queue<Node> pq;

    // Start node: city 0
    Node root(0, 0, calculateBound(graph, Node(0, 0, 0, {0}, size)), {0}, size);
    root.visited[0] = true;
    pq.push(root);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // If reached the last level, complete the tour by returning to the start
        if (current.level == size - 1) {
            int lastToFirst = graph.getEdgeWeight(current.path.back(), 0);
            if (lastToFirst != INT_MAX) {
                int totalCost = current.pathCost + lastToFirst;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = current.path;
                    bestPath.push_back(0);  // Complete the cycle
                }
            }
            continue;
        }

        // Generate children nodes for the current node
        for (int i = 0; i < size; i++) {
            if (!current.visited[i]) {
                std::vector<int> newPath = current.path;
                newPath.push_back(i);

                Node child(current.level + 1,
                           current.pathCost + graph.getEdgeWeight(current.path.back(), i),
                           0, newPath, size);
                child.visited = current.visited;
                child.visited[i] = true;

                // Calculate bound and prune if bound exceeds current minimum cost
                child.bound = calculateBound(graph, child);
                if (child.bound < minCost) {
                    pq.push(child);
                }
            }
        }
    }
}

// Public solve method
void BranchAndBound::solve(AdjacencyMatrix &graph) {
    minCost = INT_MAX;
    bestPath.clear();
    solveATSP(graph);
    shortestPathLength = minCost;
}

// Generates a string representation of the path
std::string BranchAndBound::toString() {
    std::string path;
    for (size_t i = 0; i < bestPath.size(); ++i) {
        path += std::to_string(bestPath[i]);
        if (i < bestPath.size() - 1) {
            path += " -> ";
        }
    }
    return path;
}
