# This is what the final CMakeList file may look like
cmake_minimum_required(VERSION 3.0)
project(miniSQL)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/API api)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/BufferManager buffer)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/IndexManager index)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/CatalogManager catalog)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/RecordManager record)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/Interpreter interpreter)

# link_directories(${BM_LIB} ${CM_LIB} ${RM_LIB} ${IM_LIB} ${IT_LIB})
# link_directories(${BM_LIB} ${IM_LIB})
# Executable

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)
add_executable(${PROJECT_NAME} ${api} ${buffer} ${index} ${catalog} ${interpreter} main.cpp)
# add_executable(minSQL ${API} main.cpp)