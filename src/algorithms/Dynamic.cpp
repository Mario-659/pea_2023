#include "Dynamic.h"

Dynamic::Dynamic() : TSPSolver(), graph(nullptr) {}

void Dynamic::initializeTables() {
    int size = graph->getSize();
    memo.assign(size, std::vector<int>(1 << size, -1));
    parent.assign(size, std::vector<int>(1 << size, -1));
}

int Dynamic::findMinConst(int pos, int visited) {
    int size = graph->getSize();

    // Return cost to starting point if all nodes are visited
    if (visited == ((1 << size) - 1)) {
        return graph->getEdgeWeight(pos, 0);  // Return to starting point
    }

    // Return if the path is already computed
    if (memo[pos][visited] != -1) {
        return memo[pos][visited];
    }

    int answer = std::numeric_limits<int>::max();

    // Try to go to an unvisited vertex
    for (int city = 0; city < size; city++) {
        if (!(visited & (1 << city))) {
            int newAnswer = graph->getEdgeWeight(pos, city) + findMinConst(city, visited | (1 << city));
            if (newAnswer < answer) {
                answer = newAnswer;
                parent[pos][visited] = city;  // Store the path
            }
        }
    }

    return memo[pos][visited] = answer;
}

void Dynamic::buildPath() {
    bestPath.clear();

    int size = graph->getSize();
    int visited = 1;
    int current = 0;
    bestPath.push_back(current);

    while (visited != (1 << size) - 1) {
        current = parent[current][visited];  // Move to the next city
        visited |= (1 << current);  // Mark the city as visited
        bestPath.push_back(current);
    }

    // return to starting node
    bestPath.push_back(0);
}

void Dynamic::solve(AdjacencyMatrix &graph) {
    this->graph = &graph;
    this->size = graph.getSize();

    initializeTables();

    // Find minimal cost starting from node 0
    shortestPathLength = findMinConst(0, 1);

    // Build the best path based on min cost and memo
    buildPath();
}

std::string Dynamic::toString() {
    std::string path;
    for (size_t i = 0; i < bestPath.size(); ++i) {
        path += std::to_string(bestPath[i]);
        if (i < bestPath.size() - 1) {
            path += " -> ";
        }
    }
    return path;
}
