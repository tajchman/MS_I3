cmake_minimum_required(VERSION 3.10)

project(Sections)
enable_testing()

find_package(OpenMP REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qdiag-disable:1786,3180")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -diag-disable=1786,3180")
  endif()
endif()

add_subdirectory(tools)
include_directories(tools)

add_executable(
  fib_seq 
  main_seq.cxx
)
target_link_libraries(fib_seq PUBLIC tools)

install(TARGETS fib_seq DESTINATION .)
 
add_test(NAME fib_seq COMMAND fib_seq WORKING_DIRECTORY ${TEST_DIR})

add_executable(
  fib_sections 
  main_sections.cxx
)

target_link_libraries(fib_sections PUBLIC tools OpenMP::OpenMP_CXX)
install(TARGETS fib_sections DESTINATION .)

add_test(NAME fib_sections COMMAND fib_sections WORKING_DIRECTORY ${TEST_DIR})

