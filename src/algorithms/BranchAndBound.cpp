#include "BranchAndBound.h"
#include "Heap.h"
#include <climits>
#include <algorithm>

BranchAndBound::BranchAndBound() : TSPSolver(), minCost(INT_MAX) {}

// Precompute the minimum outgoing edge cost for each node
void BranchAndBound::precomputeMinEdges(const AdjacencyMatrix &graph) {
    int size = graph.getSize();
    minOutgoingEdges.resize(size, INT_MAX);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j) {
                minOutgoingEdges[i] = std::min(minOutgoingEdges[i], graph.getEdgeWeight(i, j));
            }
        }
    }
}

// Calculate the lower bound of a path starting at the given node
int BranchAndBound::calculateBound(const AdjacencyMatrix &graph, const Node &node) {
    int bound = node.pathCost;
    int size = graph.getSize();

    for (int i = 0; i < size; ++i) {
        if (!node.visited[i]) {
            bound += minOutgoingEdges[i];
        }
    }

    return bound;
}

void BranchAndBound::solve(AdjacencyMatrix &graph) {
    minCost = INT_MAX;
    bestPath.clear();

    int size = graph.getSize();
    precomputeMinEdges(graph);

    Heap<Node> pq(size * size);

    // Start from node 0
    Node root(0, 0, 0, {0}, size);
    root.visited[0] = true;
    root.bound = calculateBound(graph, root);

    pq.push(root);

    while (pq.getSize() != 0) {
        Node current = pq.extractMin();

        // If reached the last level, close the cycle and update the best path
        if (current.level == size - 1) {
            int lastToFirst = graph.getEdgeWeight(current.path.back(), 0);
            if (lastToFirst != INT_MAX) {
                int totalCost = current.pathCost + lastToFirst;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = current.path;
                    bestPath.push_back(0);
                    std::cout << "calculated new min cost: " << minCost << std::endl;
                }
            }
            continue;
        }

        // Expand the current node
        for (int i = 0; i < size; ++i) {
            if (current.visited[i]) continue;

            Node child = current;
            child.level++;
            child.pathCost += graph.getEdgeWeight(current.path.back(), i);
            child.path.push_back(i);
            child.visited[i] = true;
            child.bound = calculateBound(graph, child);

            if (child.bound < minCost) {
                pq.push(child);
            }
        }
    }

    shortestPathLength = minCost;
}

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
