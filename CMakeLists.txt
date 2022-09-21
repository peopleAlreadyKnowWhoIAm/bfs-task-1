cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

project(mgraph)

add_library(mgraph STATIC src/mgraph.cpp include/mgraph.hpp)
target_include_directories(mgraph PUBLIC include)

enable_testing()

add_executable(mgraph_test tests/test.cpp)
target_link_libraries(mgraph_test mgraph)
