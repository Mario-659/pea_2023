#include "BranchAndBound.h"
#include "Heap.h"
#include <climits>

BranchAndBound::BranchAndBound() : TSPSolver(), minCost(INT_MAX) {}

int calculateMSTCost(const AdjacencyMatrix &graph, const std::vector<bool> &visited) {
    int size = graph.getSize();
    std::vector<int> minEdgeWeights(size, INT_MAX); // min edge weight to include node
    std::vector<bool> visitedInMST(size, false);

    // start MST from any unvisited node
    int startNode = 0;
    while (startNode < size && visited[startNode]) {
        startNode++;
    }

    // all nodes are visited
    if (startNode == size) return 0;

    minEdgeWeights[startNode] = 0;
    int mstCost = 0;

    for (int count = 0; count < size; count++) {
        int current = -1;

        // find the unvisited node with the path cost
        for (int i = 0; i < size; i++) {
            if (!visitedInMST[i] && (current == -1 || minEdgeWeights[i] < minEdgeWeights[current])) {
                current = i;
            }
        }

        // if no more nodes to include in MST end
        if (current == -1 || minEdgeWeights[current] == INT_MAX) break;

        visitedInMST[current] = true;

        mstCost += minEdgeWeights[current];

        // update minimal path costs of adjacent nodes
        for (int v = 0; v < size; v++) {
            if (!visitedInMST[v] && !visited[v] && graph.getEdgeWeight(current, v) < minEdgeWeights[v]) {
                minEdgeWeights[v] = graph.getEdgeWeight(current, v);
            }
        }
    }

    return mstCost;
}

// calculate the lower bound of a path starting at the given node
int BranchAndBound::calculateBound(const AdjacencyMatrix &graph, const Node &node) {
    int bound = node.pathCost;

    // add MST cost for remaining unvisited nodes
    int mstCost = calculateMSTCost(graph, node.visited);
    bound += mstCost;

    return bound;
}



void BranchAndBound::solve(AdjacencyMatrix &graph) {
    minCost = INT_MAX;
    bestPath.clear();
    int size = graph.getSize();
    Heap<Node> pq(size * size);

    // Start from node 0
    Node root(0, 0, 0, {0}, size);
    root.visited[0] = true;

    pq.push(root);

    while (pq.getSize() != 0) {
        Node current = pq.extractMin();

        // prune nodes with bounds greater than the current minimal cost
        if (current.bound >= minCost) continue;

        // if reached the last level, close the cycle and update the best path
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

        // expand the current node
        for (int i = 0; i < size; ++i) {
            if (current.visited[i]) continue;

            int edgeWeight = graph.getEdgeWeight(current.path.back(), i);
            if (edgeWeight == INT_MAX) continue;

            int newCost = current.pathCost + edgeWeight;

            // skip this path if its cost already exceeds the current minimum
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
