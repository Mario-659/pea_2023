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
    adj = new LinkedList<ListNode> [size];
    this->size = size;
}

void AdjacencyList::addUndEdge(int start, int end, int weight) {
    if (!validateEdge(start, end)) return;

    adj[start].pushBack({weight, end});
    adj[end].pushBack({weight, start});
}

void AdjacencyList::addEdge(int start, int end, int weight) {
    if (!validateEdge(start, end)) return;

    adj[start].pushBack({weight, end});
}


void AdjacencyList::removeEdge(int start, int end) {
    if (!validateEdge(start, end)) return;

    // TODO implement this or remove if not used (same with matrix)
//    for (int i=0; i<adj[start].size(); i++) {
//        if (adj[start][i].index == end) adj[start].erase(adj[start].begin() + i);
//    }
//
//    for (int i=0; i<adj[end].size(); i++) {
//        if (adj[end][i].index == start) adj[end].erase(adj[end].begin() + i);
//    }
}

int AdjacencyList::getSize() {
    return size;
}

std::string AdjacencyList::toString() {
    std::string text;
    for (int i=0; i<size; i++) {
        if (adj[i].size() == 0) text += "Vertex has no edges\n";
        else {
            text += std::to_string(i);
            text += " -> ";
            auto node = adj[i].getHeadNode();
            while (node != nullptr) {
                text += std::to_string(node->data.index);
                text += "(";
                text += std::to_string(node->data.weight);
                text += "), ";
                node = node->next;
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

LinkedList<ListNode>* AdjacencyList::getVertexNeighbours(int index) {
    return &adj[index];
}

int AdjacencyList::getEdge(int start, int end) {
    Node<ListNode>* ptr = adj[start].getHeadNode();
    while(ptr != nullptr) {
        if(ptr->data.index == end) return ptr->data.weight;
        ptr = ptr->next;
    }
    return INT_MAX;
}

AdjacencyList *AdjacencyList::copy() {
    auto copy = new AdjacencyList(size);

    for (int i=0; i<size; i++) {
        auto node = adj[i].getHeadNode();
        while(node != nullptr) {
            copy->addEdge(i, node->data.index, node->data.weight);
            node = node->next;
        }
    }
    return copy;
}
