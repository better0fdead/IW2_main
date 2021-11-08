cmake_minimum_required(VERSION 3.17)
project(IW_2 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g")

set(SOURCES_FOR_STATIC libs/array_search/src/array_search.c)
set(SOURCES_FOR_SHARED libs/array_search_forked/src/array_search_forked.c)

add_library(array_search STATIC ${SOURCES_FOR_STATIC})
target_include_directories(array_search PUBLIC libs/array_search/include)

add_library(array_search_forked SHARED ${SOURCES_FOR_SHARED})
target_include_directories(array_search_forked PUBLIC libs/array_search_forked/include)

find_package(GTest REQUIRED)

add_executable(main tests/tests.cpp)
target_link_libraries(main GTest::gtest array_search)

add_executable(test_stress tests/main.cpp)
target_link_libraries(test_stress array_search_forked)

add_executable(tests_forked tests/tests_forked.cpp)
target_link_libraries(tests_forked GTest::gtest array_search_forked)