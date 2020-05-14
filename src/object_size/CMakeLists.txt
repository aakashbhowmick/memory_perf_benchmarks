
# Set current directory name as the name of the target
get_filename_component(CURR_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set (TARGET_NAME ${CURR_DIR_NAME})
message(STATUS "In directory ${CURR_DIR_NAME}:")

# Glob all CPP files in directory
file(GLOB SOURCE_LIST "*.cpp")
message(STATUS "Found sources : ${SOURCE_LIST}")

# Create target executable
add_executable(${TARGET_NAME} ${SOURCE_LIST})
message(STATUS "Added executable : ${TARGET_NAME}")
