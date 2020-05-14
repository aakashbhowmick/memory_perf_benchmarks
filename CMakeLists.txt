cmake_minimum_required(VERSION 3.1)

set (PROJECT_NAME "OpenGL_Experiment")
project(${PROJECT_NAME})

# Top level directory
set(PROJECT_ROOT_PATH           ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_PATH        "${PROJECT_ROOT_PATH}/include")
set(SYSTEM_LIB_PATH     "/usr/local/lib")
set(SYSTEM_INCLUDE_PATH "/usr/local/include")

# List of source files
set (SOURCE_LIST 
     "src/window.cpp"
     "src/World.cpp"
     "src/glad.c")

# List of target dependencies
set (LIB_LIST
     "${SYSTEM_LIB_PATH}/libglfw3.a")

# List of linker flags to use
set (LINKER_FLAGS "-lGL" "-ldl" "-lpthread")

set(TARGET_NAME "experiment")
add_executable(${TARGET_NAME} ${SOURCE_LIST})
#target_sources(${TARGET_NAME} PUBLIC ${SOURCE_LIST})   
target_include_directories(${TARGET_NAME} PUBLIC ${SYSTEM_INCLUDE_PATH} ${PROJECT_INCLUDE_PATH})
target_link_libraries(${TARGET_NAME} ${LIB_LIST} ${LINKER_FLAGS})
