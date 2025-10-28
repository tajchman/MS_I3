cmake_minimum_required(VERSION 3.10)
project(Ex5)
enable_testing()

set(CMAKE_RULE_MESSAGES OFF)

add_subdirectory(tools)
include_directories(tools)

add_executable(ex_1_5 
  main.cxx 
  matrix.cxx
  )
target_link_libraries(ex_1_5 tools)

add_executable(ex_1_5b 
  main_bloc.cxx 
  matrix_bloc.cxx 
  matrix.cxx 
  )
target_link_libraries(ex_1_5b tools)

add_test(NAME ex_1_5 COMMAND ${CMAKE_INSTALL_PREFIX}/ex_1_5 -n 500 --text WORKING_DIRECTORY ${TEST_DIR})
add_test(NAME ex_1_5b COMMAND ${CMAKE_INSTALL_PREFIX}/ex_1_5b -n 500 -b 5 --text WORKING_DIRECTORY ${TEST_DIR})

install(TARGETS ex_1_5 ex_1_5b DESTINATION .)