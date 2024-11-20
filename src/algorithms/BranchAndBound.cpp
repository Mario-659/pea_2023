#include "BranchAndBound.h"
#include "Heap.h"
#include <climits>

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

int calculateMSTCost(const AdjacencyMatrix &graph, const std::vector<bool> &visited) {
    int size = graph.getSize();
    std::vector<int> key(size, INT_MAX); // Min edge weight to include node
    std::vector<bool> inMST(size, false);

    // Start MST from any unvisited node
    int startNode = 0;
    while (startNode < size && visited[startNode]) {
        startNode++;
    }

    if (startNode == size) return 0; // All nodes are visited

    key[startNode] = 0;
    int mstCost = 0;

    for (int count = 0; count < size; count++) {
        int u = -1;

        // Find the unvisited node with the smallest key value
        for (int i = 0; i < size; i++) {
            if (!inMST[i] && (u == -1 || key[i] < key[u])) {
                u = i;
            }
        }

        if (u == -1 || key[u] == INT_MAX) break; // No more nodes to include in MST

        inMST[u] = true;
        mstCost += key[u];

        // Update the key values of adjacent nodes
        for (int v = 0; v < size; v++) {
            if (!inMST[v] && !visited[v] && graph.getEdgeWeight(u, v) < key[v]) {
                key[v] = graph.getEdgeWeight(u, v);
            }
        }
    }

    return mstCost;
}

// Calculate the lower bound of a path starting at the given node
int BranchAndBound::calculateBound(const AdjacencyMatrix &graph, const Node &node) {
    int bound = node.pathCost;

    // Add MST cost for remaining unvisited nodes
    int mstCost = calculateMSTCost(graph, node.visited);
    bound += mstCost;

    return bound;
}



void BranchAndBound::solve(AdjacencyMatrix &graph) {
    minCost = INT_MAX; // Reset minCost to allow proper updates during traversal
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

        // Prune nodes with bounds greater than the current minimal cost
        if (current.bound >= minCost) continue;

        // If reached the last level, close the cycle and update the best path
        if (current.level == size - 1) {
            int lastToFirst = graph.getEdgeWeight(current.path.back(), 0);
            if (lastToFirst != INT_MAX) {
                int totalCost = current.pathCost + lastToFirst;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = current.path;  // Update best path
                    bestPath.push_back(0);    // Close the cycle
                }
            }
            continue;
        }

        // Expand the current node
        for (int i = 0; i < size; ++i) {
            if (current.visited[i]) continue;

            int edgeWeight = graph.getEdgeWeight(current.path.back(), i);
            if (edgeWeight == INT_MAX) continue;

            int newCost = current.pathCost + edgeWeight;

            // Skip this path if its cost already exceeds the current minimum
            if (newCost >= minCost) continue;

            Node child = current;
            child.level++;
            child.pathCost = newCost;
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
