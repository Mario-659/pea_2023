#ifndef PEA_DYNAMIC_H
#define PEA_DYNAMIC_H

#include "../graphs/AdjacencyMatrix.h"

#include <vector>
#include <climits>
#include <string>
#include <algorithm>

class Dynamic {
private:
    int shortestPathLength;
    int size;
    std::vector<int> bestPath;
    AdjacencyMatrix* graph;
    std::vector<std::vector<int>> memo;
    std::vector<std::vector<int>> parent;

    int tsp(int pos, int visited) {
        // Base case: all vertices are visited
        if (visited == ((1 << size) - 1)) {
            return graph->getEdge(pos, 0);  // Return to starting point
        }

        // Return if the path is already computed
        if (memo[pos][visited] != -1) {
            return memo[pos][visited];
        }

        int answer = INT_MAX;

        // Try to go to an unvisited vertex
        for (int city = 0; city < size; city++) {
            if (!(visited & (1 << city))) {
                int newAnswer = graph->getEdge(pos, city) + tsp(city, visited | (1 << city));
                if (newAnswer < answer) {
                    answer = newAnswer;
                    parent[pos][visited] = city;
                }
            }
        }

        return memo[pos][visited] = answer;
    }

    void buildPath() {
        int visited = 0;
        int current = 0;
        bestPath.push_back(0);

        while (visited != (1 << size) - 1) {
            visited |= (1 << current);
            current = parent[current][visited];
            bestPath.push_back(current);
        }
    }

public:
    Dynamic() : shortestPathLength(INT_MAX), size(0) {}

    void findShortestPath(AdjacencyMatrix &graph) {
        this->graph = &graph;
        this->size = graph.getSize();
        memo.assign(size, std::vector<int>(1 << size, -1));
        parent.assign(size, std::vector<int>(1 << size, -1));

        shortestPathLength = tsp(0, 1);  // Start from city 0
        buildPath();
    }

    int getShortestPathLength() const { return shortestPathLength; }

    std::string toString() {
        std::string path = "0 -> ";
        for (int i : bestPath) {
            path += std::to_string(i) + " -> ";
        }
        path += "0";
        return path;
    }

};


#endif //PEA_DYNAMIC_H
