cmake_minimum_required(VERSION 3.10)
project(Ex2)
enable_testing()

set(CMAKE_RULE_MESSAGES OFF)

add_subdirectory(tools)
include_directories(tools)

add_executable(ex_1_2 main.cxx init.cxx calcul.cxx)
target_link_libraries(ex_1_2 tools)

add_test(NAME ex_1_2 COMMAND ${CMAKE_INSTALL_PREFIX}/../run.py --text WORKING_DIRECTORY ${TEST_DIR})
install(TARGETS ex_1_2 DESTINATION .)
