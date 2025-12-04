cmake_minimum_required(VERSION 3.10)

project(ExempleTBB)

enable_testing()

set(CMAKE_RULE_MESSAGES OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(TBB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../local/tbb/include)
set(TBB_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/../local/tbb/lib ${CMAKE_SOURCE_DIR}/../local/tbb/lib64)

include_directories(tools ${TBB_INCLUDE_DIR})
add_subdirectory(tools)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

link_directories(
  ${TBB_LIBRARY_DIRS}
)

add_executable(
  exemple_par 
  main_par.cxx
  matrix.cxx
)

target_link_libraries(
  exemple_par tools tbb)

add_test(NAME exemple_par COMMAND ${CMAKE_INSTALL_PREFIX}/exemple_par --n 200 WORKING_DIRECTORY ${TEST_DIR})

add_executable(
  exemple_seq 
  main_seq.cxx
  matrix.cxx
)

target_link_libraries(
  exemple_seq tools)
  
add_test(NAME exemple_seq COMMAND ${CMAKE_INSTALL_PREFIX}/exemple_seq --n 200 WORKING_DIRECTORY ${TEST_DIR})
install(TARGETS exemple_seq exemple_par DESTINATION .)


