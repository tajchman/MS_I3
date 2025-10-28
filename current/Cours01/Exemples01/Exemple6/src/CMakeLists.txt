cmake_minimum_required(VERSION 3.10)
project(Ex6)
enable_testing()

set(CMAKE_RULE_MESSAGES OFF)

add_subdirectory(tools)
include_directories(tools)

foreach(t 0 0b 0c 1 1b 1c)
  add_executable(ex${t}  main${t}.cxx)
  target_link_libraries(ex${t} tools)
  add_test(NAME ex${t} COMMAND ${CMAKE_INSTALL_PREFIX}/ex${t} --n 10000000 WORKING_DIRECTORY ${TEST_DIR})
  install(TARGETS ex${t} DESTINATION .)
endforeach(t 0 0b 1 1b)

