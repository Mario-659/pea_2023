include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set(BINARY ${CMAKE_PROJECT_NAME}_tst)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(TEST_SOURCES
        main.cpp
        UtilsTest.cpp
        HeapTest.cpp
        PrimTest.cpp
        KruskalTest.cpp
        MergeSortTest.cpp
        DijkstraTest.cpp
        BellmanFordTest.cpp
        GraphTest.cpp
        BruteForceTest.cpp)

add_executable(${CMAKE_PROJECT_NAME}_tst ${TEST_SOURCES})

add_test(NAME ${CMAKE_PROJECT_NAME}_tst COMMAND ${CMAKE_PROJECT_NAME}_tst)

target_link_libraries(${CMAKE_PROJECT_NAME}_tst PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

# Copy the test/resources directory to the location of the test executable
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_tst POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/test/resources $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}_tst>/resources)

