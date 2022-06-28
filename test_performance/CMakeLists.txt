set(BINARY ${CMAKE_PROJECT_NAME}_perf)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(PERF_SRC
        main.cpp
        MSTTest.cpp
        MSTTest.h
        PathTest.h
        PathTest.cpp
        )

add_executable(${CMAKE_PROJECT_NAME}_perf ${PERF_SRC})

target_link_libraries(${CMAKE_PROJECT_NAME}_perf PUBLIC ${CMAKE_PROJECT_NAME}_lib)
