set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        main.cpp
        utils/Utils.h
        utils/Utils.cpp
        graphs/AdjacencyList.h
        graphs/AdjacencyList.cpp
        graphs/AdjacencyMatrix.h
        graphs/AdjacencyMatrix.cpp
        algorithms/Prim.h
        algorithms/Prim.cpp
        algorithms/Heap.h
        )

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
