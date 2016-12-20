cmake_minimum_required(VERSION 3.7.1)
project (FANN_ANALYSIS)

enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_MACOSX_RPATH 1)
set (EXEC execProject)
set (SOURCE src/experiment.cpp)

configure_file(CMakeLists.txt.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
 
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

find_package(fann)
 
## Create Executable
add_executable(${EXEC} ${SOURCE})
target_include_directories(${EXEC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)
target_link_libraries(${EXEC} fann)
