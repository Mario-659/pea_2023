cmake_minimum_required(VERSION 3.21)
project(PEA)

set(CMAKE_CXX_STANDARD 17)

set(GOOGLETEST_VERSION 1.10.0)

enable_testing()

add_subdirectory(src)

add_subdirectory(test)

add_subdirectory(test_performance)
