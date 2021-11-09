cmake_minimum_required(VERSION 3.17)
project(IW_2 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pthread -pedantic -g --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pthread -pedantic -g --coverage")

set(SOURCES_FOR_STATIC libs/array_search/src/array_search.c)
set(SOURCES_FOR_SHARED libs/array_search_forked/src/array_search_forked.c)

add_library(array_search STATIC ${SOURCES_FOR_STATIC})
target_include_directories(array_search PUBLIC libs/array_search/include)

add_library(array_search_forked SHARED ${SOURCES_FOR_SHARED})
target_include_directories(array_search_forked PUBLIC libs/array_search_forked/include)

find_package(GTest REQUIRED)

add_executable(test_normal tests/test_normal.cpp)
target_link_libraries(test_normal GTest::gtest array_search)

add_executable(test_forked tests/tests_forked.cpp)
target_link_libraries(test_forked GTest::gtest array_search_forked)

add_executable(stress_test tests/stress_test_normal.cpp)
target_link_libraries(stress_test array_search)

add_executable(stress_test_forked tests/stress_test_forked.cpp)
target_link_libraries(stress_test_forked array_search_forked)