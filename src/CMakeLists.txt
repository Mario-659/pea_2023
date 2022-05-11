set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        main.cpp
        Hello.h
        Hello.cpp
        )

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})