set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        main.cpp
        utils/Utils.h
        utils/Utils.cpp
        graphs/AdjacencyList.h
        graphs/AdjacencyList.cpp
        graphs/AdjacencyMatrix.h
        graphs/AdjacencyMatrix.cpp
        graphs/Edge.h
        algorithms/Prim.h
        algorithms/Prim.cpp
        algorithms/Kruskal.h
        algorithms/Kruskal.cpp
        algorithms/MergeSort.h
        algorithms/Heap.h
        algorithms/LinkedList.h
        algorithms/Dijkstra.h
        algorithms/Dijkstra.cpp
        algorithms/BellmanFord.h
        algorithms/BellmanFord.cpp
        algorithms/BruteForce.cpp
        algorithms/BruteForce.h
        algorithms/BranchAndBound.cpp
        algorithms/BranchAndBound.h
        )

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
