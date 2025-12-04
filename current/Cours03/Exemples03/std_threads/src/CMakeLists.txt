cmake_minimum_required(VERSION 3.10)

project(STDTHREADS)

set(CMAKE_RULE_MESSAGES OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Threads REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qdiag-disable:1786,3180")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -diag-disable=1786,3180")
  endif()
endif()

include_directories(tools ${TBB_INCLUDE_DIR})
add_subdirectory(tools)

add_executable(
  exemple_par 
  main_par.cxx
  matrix.cxx
  )

target_link_libraries(
  exemple_par
  tools
  ${CMAKE_THREAD_LIBS_INIT})

add_executable(
  exemple_seq 
  main_seq.cxx
  matrix.cxx
  )

target_link_libraries(
  exemple_seq
  tools)

install(TARGETS exemple_seq exemple_par DESTINATION .)


