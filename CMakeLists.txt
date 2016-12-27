cmake_minimum_required(VERSION 3.7.1)
project (FANN_ANALYSIS)

enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_MACOSX_RPATH 1)
set (EXEC execProject)
set (SOURCE src/inputs.cpp src/netGradient.cpp)
set (EXEC_SOURCE src/experiment.cpp)
set (WRAPPER_DIR /Users/klinkhae/research/cpp_ws/fann-cpp-vector)
set (TEST_SOURCE test/inputs_test.cpp)
set (TEST_EXEC runUnitTests)

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
add_executable(${EXEC} ${SOURCE} ${EXEC_SOURCE})
target_include_directories(${EXEC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include ${WRAPPER_DIR}/include)
target_link_libraries(${EXEC} fann)
target_link_libraries(${EXEC} ${WRAPPER_DIR}/cmake/libFANN_Wrapper.a)

enable_testing()
add_executable(${TEST_EXEC} ${TEST_SOURCE} ${SOURCE})
target_link_libraries(${TEST_EXEC} gtest gtest_main fann)
target_include_directories(${TEST_EXEC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include ${WRAPPER_DIR}/include)
target_link_libraries(${TEST_EXEC} ${WRAPPER_DIR}/cmake/libFANN_Wrapper.a)
add_test(NAME gtest-${LIB_NAME} COMMAND ${TEST_EXEC})
