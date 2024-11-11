#include "BranchAndBound.h"
#include "Heap.h"
#include <climits>

BranchAndBound::BranchAndBound() : TSPSolver(), minCost(INT_MAX) {}

// calculate lower bound of a path starting at the given node
int BranchAndBound::calculateBound(const AdjacencyMatrix &graph, const Node &node) {
    int bound = node.pathCost;
    int size = graph.getSize();
    int lastVisited = node.path.back();

    // for each unvisited node add minimum outgoing edge costs
    for (int i = 0; i < size; i++) {
        if (node.visited[i] || i == lastVisited) continue;

        int minEdge = INT_MAX;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                minEdge = std::min(minEdge, graph.getEdgeWeight(i, j));
            }
        }
        bound += (minEdge == INT_MAX) ? 0 : minEdge;
    }

    return bound;
}

void BranchAndBound::solve(AdjacencyMatrix &graph) {
    minCost = INT_MAX;
    bestPath.clear();

    int size = graph.getSize();
    Heap<Node> pq(size * size);

    // start from node 0
    int initialBound = calculateBound(graph, Node(0, 0, 0, {0}, size));
    Node root(0, 0, initialBound, {0}, size);
    root.visited[0] = true;
    pq.push(root);

    while (pq.getSize() != 0) {
        Node current = pq.extractMin();

        // if reached the last level, return to initial node 0
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

        // for each unvisited children node of current node
        for (int i = 0; i < size; i++) {
            if (current.visited[i]) continue;

            std::vector<int> newPath = current.path;
            newPath.push_back(i);

            Node child(current.level + 1,
                       current.pathCost + graph.getEdgeWeight(current.path.back(), i),
                       0, newPath, size);
            child.visited = current.visited;
            child.visited[i] = true;

            child.bound = calculateBound(graph, child);
            // disregard path if bound is greater or equal to current minimal cost
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
