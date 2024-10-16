#include "BranchAndBound.h"
#include "Heap.h"


int BranchAndBound::TSPBound(AdjacencyMatrix &matrix, Node &u) {
    int bound = 0;
    std::vector<bool> visited(size, false);

    for (int i : u.path) {
        visited[i] = true;
    }

    for (int i = 0; i < size; i++) {
        if (visited[i]) continue;
        int min1 = std::numeric_limits<int>::max();
        int min2 = std::numeric_limits<int>::max();
        for (int j = 0; j < size; j++) {
            if (i != j && !visited[j]) {
                int edgeCost = matrix.getEdge(i, j);
                if (edgeCost < min1) {
                    min2 = min1;
                    min1 = edgeCost;
                } else if (edgeCost < min2) {
                    min2 = edgeCost;
                }
            }
        }
        if (min1 != std::numeric_limits<int>::max()) {
            bound += min1 + min2;
        }
    }

    return (bound / 2);
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
