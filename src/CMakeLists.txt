set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        main.cpp
        utils/Utils.h
        utils/Utils.cpp
        )

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})