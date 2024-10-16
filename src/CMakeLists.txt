set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        main.cpp
        utils/Utils.h
        utils/Utils.cpp
        graphs/AdjacencyMatrix.h
        graphs/AdjacencyMatrix.cpp
        algorithms/BruteForce.cpp
        algorithms/BruteForce.h
        algorithms/BranchAndBound.cpp
        algorithms/BranchAndBound.h
        )

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} algorithms/Dynamic.cpp algorithms/Dynamic.h)


