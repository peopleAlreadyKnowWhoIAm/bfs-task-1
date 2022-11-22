cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

project(mgraph)

add_library(mgraph STATIC src/mgraph.cpp include/mgraph.hpp)
target_include_directories(mgraph PUBLIC include)


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  mgraph_test
  tests/test.cpp
)
target_link_libraries(
  mgraph_test
  GTest::gtest_main
  mgraph
)

include(GoogleTest)
gtest_discover_tests(mgraph_test)

add_executable(mgraph_exec main.cpp)
target_link_libraries(mgraph_exec mgraph)