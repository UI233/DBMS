cmake_minimum_required(VERSION 3.0)
project(BufferManager)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
set(LIBRARY_OUTPUT_PATH ../lib)
# SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(BufferManager ${SRC_LIST})
# add_executable(test ${SRC_LIST})
