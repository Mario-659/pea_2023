#include <iostream>

#include "graphs/AdjacencyList.h"
#include "graphs/AdjacencyMatrix.h"

#include "algorithms/Prim.h"


int main(){
//    AdjacencyMatrix graph(5);
//    std::cout << graph.toString() << std::endl;
//
//    graph.addEdge(5, 3, 11);
//    std::cout << graph.toString() << std::endl;
//
//    graph.addEdge(0, 3, 11);
//    std::cout << graph.toString() << std::endl;
//
//    graph.addEdge(0, 4, 22);
//    std::cout << graph.toString() << std::endl;
//
//    graph.addEdge(2, 3, 22);
//    std::cout << graph.toString() << std::endl;
//
//    graph.removeEdge(2, 3);
//    std::cout << graph.toString() << std::endl;
//
//    std::cout << "hello world" << std::endl;

    AdjacencyMatrix graph(5);
    graph.addEdge(0, 1, 11);
    graph.addEdge(1, 2, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 3);
    graph.addEdge(2, 3, 22);
    graph.addEdge(3, 4, 9);
    std::cout << graph.toString() << std::endl;

    Prim prim;
    prim.mst(graph);

    std::cout << prim.toString() << std::endl;
}