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

    // Recursive function to calculate the minimum weight of the TSP
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
                    parent[pos][visited] = city;  // Store the path
                }
            }
        }

        return memo[pos][visited] = answer;
    }

    // Build the path from the computed parent information
    void buildPath() {
        int visited = 1;  // Start with city 0 visited
        int current = 0;  // Start from city 0
        bestPath.clear();  // Clear any existing path
        bestPath.push_back(current);  // Start from city 0

        while (visited != (1 << size) - 1) {
            current = parent[current][visited];  // Move to the next city
            visited |= (1 << current);  // Mark the city as visited
            bestPath.push_back(current);
        }
        bestPath.push_back(0);  // Return to starting point
    }

public:
    Dynamic() : shortestPathLength(INT_MAX), size(0) {}

    // Function to find the shortest path using dynamic programming
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
        std::string path;
        for (size_t i = 0; i < bestPath.size(); ++i) {
            path += std::to_string(bestPath[i]);
            if (i < bestPath.size() - 1) {
                path += " -> ";
            }
        }
        return path;
    }
};


#endif //PEA_DYNAMIC_H
