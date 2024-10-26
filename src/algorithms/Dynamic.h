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
    int findMinConst(int pos, int visited) {

        // return cost to starting point if all nodes are visited
        if (visited == ((1 << size) - 1)) {
            return graph->getEdge(pos, 0);  // Return to starting point
        }

        // return if the path is already computed
        if (memo[pos][visited] != -1) {
            return memo[pos][visited];
        }

        int answer = std::numeric_limits<int>::max();

        // try to go to an unvisited vertex
        for (int city = 0; city < size; city++) {
            if (!(visited & (1 << city))) {
                int newAnswer = graph->getEdge(pos, city) + findMinConst(city, visited | (1 << city));
                if (newAnswer < answer) {
                    answer = newAnswer;
                    parent[pos][visited] = city;  // Store the path
                }
            }
        }

        return memo[pos][visited] = answer;
    }

    void buildPath() {
        bestPath.clear();

        // start from city 0
        int visited = 1;
        int current = 0;
        bestPath.push_back(current);

        while (visited != (1 << size) - 1) {
            current = parent[current][visited];  // move to the next city
            visited |= (1 << current);  // mark the city as visited
            bestPath.push_back(current);
        }

        // add return to starting node
        bestPath.push_back(0);
    }

public:
    Dynamic() : shortestPathLength(std::numeric_limits<int>::max()), size(0) {}

    void solve(AdjacencyMatrix &graph) {
        this->graph = &graph;
        this->size = graph.getSize();

        // init memo table
        memo.assign(size, std::vector<int>(1 << size, -1));

        parent.assign(size, std::vector<int>(1 << size, -1));

        // find minimal cost starting from node 0
        shortestPathLength = findMinConst(0, 1);

        // find the best path based on min cost and memo
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
