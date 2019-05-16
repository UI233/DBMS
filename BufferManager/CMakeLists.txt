cmake_minimum_required(VERSION 3.0)
project(BufferManager)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
include_directories(../)
add_library(BufferManager ${SRC_LIST})