cmake_minimum_required(VERSION 3.10)
project(Ex3)
enable_testing()

set(CMAKE_RULE_MESSAGES OFF)

add_executable(ex_1_3 main.c init.c calcul.c timer.c)
add_test(NAME ex_1_3 COMMAND ${CMAKE_INSTALL_PREFIX}/../run.py -n 4 --text WORKING_DIRECTORY ${TEST_DIR})
install(TARGETS ex_1_3 DESTINATION .)
