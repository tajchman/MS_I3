
set(code "sinus_omp_coarse_grain")

set(CMAKE_RULE_MESSAGES OFF)
set(CMAKE_BUILD_TYPE Release)

find_package(OpenMP REQUIRED)

add_executable(${code}
  main.cxx
  calcul.cxx
  parameters.cxx
)

target_link_libraries(${code} PUBLIC communs tools OpenMP::OpenMP_CXX)

add_test(NAME ${code} COMMAND ${code} WORKING_DIRECTORY ${TEST_DIR})
set_property(TEST ${code} PROPERTY ENVIRONMENT "OMP_NUM_THREADS=3")

install(TARGETS ${code} DESTINATION .)


