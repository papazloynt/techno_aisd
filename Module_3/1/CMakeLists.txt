cmake_minimum_required(VERSION 3.21)
project(1)

set(CMAKE_CXX_STANDARD 17)

# Abstract
add_library(abstract INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/igraph/abstract_graph.h)

# ARC
add_library(arc STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/arcgraph/arc_graph.cpp)
target_include_directories(arc PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/arcgraph
        ${CMAKE_CURRENT_SOURCE_DIR}/igraph)
target_link_libraries(arc
        abstract)

# List
add_library(list STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/listgraph/list_graph.cpp)
target_include_directories(list PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/listgraph
        ${CMAKE_CURRENT_SOURCE_DIR}/igraph)
target_link_libraries(list
        abstract)

# Matrix
add_library(matrix STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/matrixgraph/matrix_graph.cpp)
target_include_directories(matrix PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/matrixgraph
        ${CMAKE_CURRENT_SOURCE_DIR}/igraph)
target_link_libraries(matrix
        abstract)

# Set
add_library(set STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/setgraph/set_graph.cpp)
target_include_directories(matrix PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/setgraph
        ${CMAKE_CURRENT_SOURCE_DIR}/igraph)
target_link_libraries(set
        abstract)

# Example
add_executable(1
        main.cpp)
target_include_directories(1 PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/setgraph
        ${CMAKE_CURRENT_SOURCE_DIR}/arcgraph
        ${CMAKE_CURRENT_SOURCE_DIR}/matrixgraph
        ${CMAKE_CURRENT_SOURCE_DIR}/listgraph)
target_link_libraries(1
        arc
        list
        matrix
        set)

