cmake_minimum_required(VERSION 3.10)
project(Ex4)
enable_testing()

set(CMAKE_RULE_MESSAGES OFF)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_compile_options(-O0)
  add_link_options(-O0)
endif()

add_executable(ex_1_4 main.c init.c calcul.c timer.c)
add_test(NAME ex_1_4 COMMAND ${CMAKE_INSTALL_PREFIX}/ex_1_4 WORKING_DIRECTORY ${TEST_DIR})
install(TARGETS ex_1_4 DESTINATION .)

