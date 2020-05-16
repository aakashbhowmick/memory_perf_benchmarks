cmake_minimum_required(VERSION 3.1)

set (PROJECT_NAME "mem_perf_benchmark")
project(${PROJECT_NAME})

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("./src/object_size")
