#include "Kruskal.h"

int Subset::find(Subset* subsets, int element) {
    // path compression
    if (subsets[element].parent != element)
        subsets[element].parent = find(subsets, subsets[element].parent);
    return subsets[element].parent;
}

void Subset::setUnion(Subset * subsets, int u, int v) {
    // find roots for elements u and v
    int root1 = find(subsets, u);
    int root2 = find(subsets, v);

    // when joining ranks stay the same if are different
    if (subsets[root1].rank < subsets[root2].rank)
        subsets[root1].parent = root2;
    else if (subsets[root1].rank > subsets[root2].rank)
        subsets[root2].parent = root1;
    else {
        // joining elements with the same ranks increases height of the tree
        subsets[root2].parent = root1;
        subsets[root1].rank++;
    }
}

void Kruskal::mst(AdjacencyMatrix graph) {
    // linked list containing edges of the graph
    LinkedList<Edge> edges;

    // adding edges to the list
    // (matrix is symmetric because given graph is undirected)
    int diag = 1;
    for (int i = 0; i < graph.getSize(); i++) {
        for (int j = 0; j < diag; j++) {
            int weight = graph.getEdge(i, j);
            if (weight != INT_MAX) {
                Edge item = { i, j, weight };
                edges.pushBack(item);
            }
        }
        diag++;
    }

    // sort edges ascending
    mergeSort(&edges);

    // allocate memory for subsets
    Subset* subsets = new Subset[graph.getSize()];

    // for every subset set parent as vertex and rank = 0
    for (int i = 0; i < graph.getSize(); i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int edgeIndex = 0;
    while (edgeList.size() < graph.getSize() - 1) {
        Edge currentEdge = edges.get(edgeIndex);
        edgeIndex++;

        // find sets for start and end of the edge
        int start = Subset::find(subsets, currentEdge.start);
        int end = Subset::find(subsets, currentEdge.end);

        // if vertexes are in different subsets, join them and add edge to list with mst
        if (start != end) {
            edgeList.pushBack(currentEdge);
            Subset::setUnion(subsets, start, end);
        }
    }
    delete[] subsets;
}

void Kruskal::mst(AdjacencyList graph) {
    LinkedList<Edge> edges;

    // add all edges to the list
    for (int i = 0; i < graph.getSize(); i++) {
        LinkedList<ListNode>* row = graph.getVertexNeighbours(i);
        Node<ListNode>* node = row->getHeadNode();
        while (node != nullptr) {
            Edge item = { i, node->data.index, node->data.weight };
            if (!edges.contains(item)) edges.pushBack(item);
            node = node->next;
        }
    }

    // from here do the same as with matrix

    mergeSort(&edges);

    Subset* subsets = new Subset[graph.getSize()];
    for (int i = 0; i < graph.getSize(); i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int edgeIndex = 0;
    while (edgeList.size() < graph.getSize() - 1) {
        Edge currentEdge = edges.get(edgeIndex);
        edgeIndex++;

        int start = Subset::find(subsets, currentEdge.start);
        int end = Subset::find(subsets, currentEdge.end);
        if (start != end) {
            edgeList.pushBack(currentEdge);
            Subset::setUnion(subsets, start, end);
        }
    }
    delete[] subsets;
}

LinkedList<Edge>* Kruskal::getEdgeList() {
    return &edgeList;
}

void Kruskal::clear() {
    edgeList.clear();
}

int Kruskal::getPathLen() {
    Node<Edge>* node = edgeList.getHeadNode();
    int sum = 0;
    while(node != nullptr) {
        sum += node->data.weight;
        node = node->next;
    }
    return sum;
}

std::string Kruskal::toString() {
    std::string text("Edges in MST: \n");

    Node<Edge>* head = edgeList.getHeadNode();
    while (head != nullptr) {
        auto edge = head->data;
        text += std::to_string(edge.start);
        text += ", ";
        text += std::to_string(edge.end);
        text += ", weight ";
        text += std::to_string(edge.weight);
        text += "\n";
        head = head->next;
    }
    text += "Weight of the tree: ";
    text += std::to_string(getPathLen());
    text += "\n";
    return text;
}

Kruskal::Kruskal() = default;

Kruskal::~Kruskal() = default;
