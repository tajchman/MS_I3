cmake_minimum_required(VERSION 3.10)
project(Ex1)
enable_testing()

set(CMAKE_RULE_MESSAGES OFF)
set(CMAKE_INSTALL_MESSAGE LAZY)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_compile_options(-O0)
  add_link_options(-O0)
endif()

add_subdirectory(tools)
include_directories(tools)

add_executable(ex_1_1 main.cxx init.cxx calcul.cxx)
target_link_libraries(ex_1_1 tools)
add_test(NAME ex_1_1 COMMAND ${CMAKE_INSTALL_PREFIX}/../run.py -n 10 -d 2 --text WORKING_DIRECTORY ${TEST_DIR})

install(TARGETS ex_1_1 DESTINATION .)
