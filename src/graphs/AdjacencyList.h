#ifndef SDIZO_2_ADJACENCYLIST_H
#define SDIZO_2_ADJACENCYLIST_H

#include <string>
#include <vector>
#include <iostream>

struct ListNode {
    int weight;

    int index;

    ListNode(int weight);

    ListNode(int weight, int index);

    ListNode() = default;

    ~ListNode() = default;

    bool operator==(const ListNode &rhs) const;

    bool operator!=(const ListNode &rhs) const;

    bool operator<(const ListNode &rhs) const;

    bool operator>(const ListNode &rhs) const;

    bool operator<=(const ListNode &rhs) const;

    bool operator>=(const ListNode &rhs) const;
};

/**
 * Undirected graph representation as list
 */
class AdjacencyList {
public:
    // Constructor for graph
    AdjacencyList(int size);

    // Adds new edge to the graph
    void addEdge(int start, int end, int weight);

    // Removes edge from the graph
    void removeEdge(int start, int end);

    std::vector<ListNode> getVertexNeighbours(int index);

    // Returns size
    int getSize();

    // Returns string representation
    std::string toString();

    ~AdjacencyList() = default;

private:
    int size;
    std::vector<ListNode>* adj;

    bool validateEdge(int start, int end);
};


#endif //SDIZO_2_ADJACENCYLIST_H
