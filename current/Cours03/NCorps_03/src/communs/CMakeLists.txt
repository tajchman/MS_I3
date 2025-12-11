cmake_minimum_required(VERSION 3.10)
project(communs)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

include(communs.cmake)

if (TIMERS)
  add_definitions(-DTIMERS=1)
endif()

add_library(communs STATIC
  parameters.cxx
  system.cxx
  parameters.cxx 
  arguments.cxx 
  pause.cxx 
  timer.cxx 
  os.cxx
  $<$<BOOL:${USE_GRAPHICS}>:display.cxx>)

install(TARGETS communs DESTINATION lib)

install(FILES 
  system.hxx 
  type.hxx 
  parameters.hxx 
  arguments.hxx
  timer.hxx
  check_cuda.cuh
  timerGPU.hxx
  DESTINATION include)

if (USE_GRAPHICS)
  install(FILES display.hxx DESTINATION include)
endif()

install(FILES
  communs.cmake
  FindGLFW3.cmake
  DESTINATION .)
