#include "AdjacencyList.h"

ListNode::ListNode(int weight, int index) {
    this->weight = weight;
    this->index = index;
}

ListNode::ListNode(int weight) {
    this->weight = weight;
}

bool ListNode::operator==(const ListNode &rhs) const {
    return weight == rhs.weight &&
           index == rhs.index;
}

bool ListNode::operator!=(const ListNode &rhs) const {
    return !(rhs == *this);
}

bool ListNode::operator<(const ListNode &rhs) const {
    return weight < rhs.weight;
}

bool ListNode::operator>(const ListNode &rhs) const {
    return rhs < *this;
}

bool ListNode::operator<=(const ListNode &rhs) const {
    return !(rhs < *this);
}

bool ListNode::operator>=(const ListNode &rhs) const {
    return !(*this < rhs);
}


AdjacencyList::AdjacencyList(int size) {
    adj = new std::vector<ListNode> [size];
    this->size = size;
}

void AdjacencyList::addEdge(int start, int end, int weight) {
    if (!validateEdge(start, end)) return;

    adj[start].emplace_back(weight, end);
    adj[end].emplace_back(weight,start);
}

void AdjacencyList::removeEdge(int start, int end) {
    if (!validateEdge(start, end)) return;

    for (int i=0; i<adj[start].size(); i++) {
        if (adj[start][i].index == end) adj[start].erase(adj[start].begin() + i);
    }

    for (int i=0; i<adj[end].size(); i++) {
        if (adj[end][i].index == start) adj[end].erase(adj[end].begin() + i);
    }
}

int AdjacencyList::getSize() {
    return size;
}

std::string AdjacencyList::toString() {
    std::string text;
    for (int i=0; i<size; i++) {
        if (adj[i].empty()) text += "Vertex has no edges\n";
        else {
            text += std::to_string(i);
            text += " -> ";
            for (auto node: adj[i]) {
                text += std::to_string(node.index);
                text += "(";
                text += std::to_string(node.weight);
                text += "), ";
            }
            text += "\n";
        }
    }
    return text;
}

bool AdjacencyList::validateEdge(int start, int end) {
    if (start < 0 || start >= size || end < 0 || end >= size) {
        std::cout << "Invalid edge operation."
                     " Given params: start:" << start << " end:" << end <<
                     " graph size:" << size << std::endl;
        return false;
    }
    return true;
}

std::vector<ListNode> AdjacencyList::getVertexNeighbours(int index) {
    return adj[index];
}
