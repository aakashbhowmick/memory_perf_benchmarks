cmake_minimum_required(VERSION 3.1)

set (PROJECT_NAME "mem_perf_benchmark")
project(${PROJECT_NAME})

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT DEFINED CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
endif()
message(STATUS "CMAKE_INSTALL_PREFIX : ${CMAKE_INSTALL_PREFIX}")

add_subdirectory("./src/object_size")
add_subdirectory("./src/matrix_access")
add_subdirectory("./src/sso")
add_subdirectory("./src/heap_alloc")
add_subdirectory("./src/vector_erase")
add_subdirectory("./src/vector_vs_set")
add_subdirectory("./src/branch_predict")
add_subdirectory("./src/false_sharing")
