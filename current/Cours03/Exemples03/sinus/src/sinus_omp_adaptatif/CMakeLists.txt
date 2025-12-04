
set(code "sinus_omp_adaptatif")

set(CMAKE_RULE_MESSAGES OFF)
set(CMAKE_BUILD_TYPE Release)

find_package(OpenMP REQUIRED)

add_executable(${code}
  main.cxx
  charge.cxx
  calcul.cxx
  parameters.cxx
)

target_link_libraries(${code} PUBLIC communs tools OpenMP::OpenMP_CXX)

install(TARGETS ${code} DESTINATION .)


