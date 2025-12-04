
set(code "sinus_seq")

set(CMAKE_RULE_MESSAGES OFF)
set(CMAKE_BUILD_TYPE Release)

add_executable(${code} 
  main.cxx
  calcul.cxx
  parameters.cxx
)

target_link_libraries(${code} communs tools)

add_test(NAME ${code} COMMAND ${code} WORKING_DIRECTORY ${TEST_DIR})

install(TARGETS ${code} DESTINATION .)

