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
    int size = graph.getSize();
    int lastVisited = node.path.back();

    // Add MST cost for remaining unvisited nodes
    bound += calculateMSTCost(graph, node.visited);

    // Add minimum outgoing edge from the last visited node
    int minOutgoing = INT_MAX;
    for (int j = 0; j < size; j++) {
        if (!node.visited[j] && graph.getEdgeWeight(lastVisited, j) < minOutgoing) {
            minOutgoing = graph.getEdgeWeight(lastVisited, j);
        }
    }
    bound += (minOutgoing == INT_MAX) ? 0 : minOutgoing;

    return bound;
}


int BranchAndBound::preSolve(AdjacencyMatrix &graph) {
    int size = graph.getSize();
    std::vector<bool> visited(size, false);
    int cost = 0;
    int current = 0;

    visited[current] = true;

    for (int i = 1; i < size; i++) {
        int next = -1;
        int minEdge = INT_MAX;

        for (int j = 0; j < size; j++) {
            if (!visited[j] && graph.getEdgeWeight(current, j) < minEdge) {
                minEdge = graph.getEdgeWeight(current, j);
                next = j;
            }
        }

        if (next != -1) {
            cost += minEdge;
            visited[next] = true;
            current = next;
        }
    }

    // Add the cost to return to the starting node
    cost += graph.getEdgeWeight(current, 0);
    return cost;
}

void BranchAndBound::solve(AdjacencyMatrix &graph) {
    minCost = preSolve(graph); // Use heuristic to initialize minCost
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

        // Prune nodes with bounds greater than current minimal cost
        if (current.bound >= minCost) continue;

        // If reached the last level, close the cycle and update the best path
        if (current.level == size - 1) {
            int lastToFirst = graph.getEdgeWeight(current.path.back(), 0);
            if (lastToFirst != INT_MAX) {
                int totalCost = current.pathCost + lastToFirst;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = current.path;
                    bestPath.push_back(0);
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
