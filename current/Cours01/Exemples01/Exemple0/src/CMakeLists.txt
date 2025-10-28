cmake_minimum_required(VERSION 3.10)
project(Ex01_0)
enable_testing()

set(CMAKE_RULE_MESSAGES OFF)
set(CMAKE_INSTALL_MESSAGE LAZY)

set(Exemple0_Options)
set(Exemple0_Release_Options -O2)
set(Exemple0_Debug_Options   -O0 -g)
set(Exemple0_RelWithDebInfo_Options -O2 -g)
set(Exemple0_Gprof_Options -pg)

foreach(v Exemple0 Exemple0_Release Exemple0_Debug Exemple0_RelWithDebInfo Exemple0_Gprof)
  add_executable(${v} main.c)
  target_compile_options(${v} PRIVATE ${${v}_Options})
  target_link_libraries(${v} m)
  target_link_options(${v} PRIVATE ${${v}_Options})
  add_test(NAME ${v} COMMAND ${v} WORKING_DIRECTORY ${TEST_DIR})
  install(TARGETS ${v} DESTINATION .)
endforeach()

add_test(NAME Exemple0_Gprof_2
         COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/run_gprof.py 
	         ${CMAKE_CURRENT_BINARY_DIR}/Exemple0_Gprof 
         WORKING_DIRECTORY ${TEST_DIR} )

set(Exemple0_2_Debug_Options -O0 -g)
set(Exemple0_2_Release_Options -O0)

foreach(v Exemple0_2_Release Exemple0_2_Debug)
  add_executable(${v} main2.c)
  target_compile_options(${v} PRIVATE ${${v}_Options})
  target_link_libraries(${v} m)
  add_test(NAME ${v} COMMAND ${CMAKE_COMMAND} $<TARGET_FILE:${v}>
           WORKING_DIRECTORY ${TEST_DIR})
  set_property(TEST ${v} PROPERTY WILL_FAIL TRUE)
  install(TARGETS ${v} DESTINATION .)
endforeach()
