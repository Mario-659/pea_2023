#include "BranchAndBound.h"


int BranchAndBound::TSPBound(AdjacencyMatrix &matrix, BaBNode u) {
    int bound = 0;
    std::vector<bool> visited(size, false);

    for (int i = 0; i < u.path.size(); i++)
        visited[u.path[i]] = true;

    for (int i = 0; i < size; i++) {
        if (visited[i]) continue;
        int min1 = NO_EDGE;
        int min2 = NO_EDGE;
        for (int j = 0; j < size; j++) {
            if (i != j && !visited[j] && matrix.getEdge(i, j) < min1) {
                min2 = min1;
                min1 = matrix.getEdge(i, j);
            } else if (i != j && !visited[j] && matrix.getEdge(i, j) < min2) {
                min2 = matrix.getEdge(i, j);
            }
        }
        bound += (min1 + min2);
    }

    return (bound / 2);
}

void BranchAndBound::findPath(AdjacencyMatrix &graph) {
    std::vector<BaBNode> nodes;

    BaBNode start;
    start.level = 0;
    start.path.push_back(0);
    start.bound = TSPBound(graph, start);

    nodes.push_back(start);

    while (!nodes.empty()) {
        // Sort the nodes based on the bound, so we always process the most promising node first
        std::sort(nodes.begin(), nodes.end());

        BaBNode curr = nodes.back();
        nodes.pop_back();

        if (curr.bound < minCost) {
            for (int i = 1; i < size; i++) {
                if (std::find(curr.path.begin(), curr.path.end(), i) == curr.path.end()) {
                    BaBNode child = curr;
                    child.path.push_back(i);
                    child.level = curr.level + 1;
                    if (child.level == size - 1) {
                        child.path.push_back(0);
                        int currCost = 0;
                        for (int j = 0; j < child.path.size() - 1; j++) {
                            currCost += graph.getEdge(child.path[j], child.path[j+1]);
                        }
                        if (currCost < minCost) {
                            minCost = currCost;
                            bestPath = child.path;
                        }
                    } else {
                        child.bound = TSPBound(graph, child);
                        if (child.bound < minCost) {
                            nodes.push_back(child);
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
    std::string path = "0 -> ";
    for (int i : bestPath) {
        path += std::to_string(i) + " -> ";
    }
    path += "0";
    return path;
}
