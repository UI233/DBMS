# This is what the final CMakeList file may look like
cmake_minimum_required(VERSION 3.0)
project(miniSQL)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
# register subprojects
add_subdirectory(BufferManager)
add_subdirectory(CatalogManager)
# add_subdirectory(RecordManager)
# add_subdirectory(IndexManager)
# add_subdirectory(Interpreter)

# register libraries
find_library(BM_LIB BufferManager ${CMAKE_CURRENT_LIST_DIR}/lib NO_DEFAULT_PATH)
find_library(CM_LIB CatalogManager ${CMAKE_CURRENT_LIST_DIR}/lib NO_DEFAULT_PATH)
# find_library(RM_LIB RecordManager ${CMAKE_CURRENT_LIST_DIR}/lib NO_DEFAULT_PATH)
# find_library(IM_LIB IndexManager ${CMAKE_CURRENT_LIST_DIR}/lib NO_DEFAULT_PATH)
# find_library(IT_LIB Interpreter ${CMAKE_CURRENT_LIST_DIR}/lib NO_DEFAULT_PATH)

# link_directories(${BM_LIB} ${CM_LIB} ${RM_LIB} ${IM_LIB} ${IT_LIB})

# Executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)
# add_executable(minSQL main.cpp)