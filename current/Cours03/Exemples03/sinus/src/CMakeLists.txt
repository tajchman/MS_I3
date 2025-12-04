cmake_minimum_required(VERSION 3.10)
project(Sinus)

set(CMAKE_RULE_MESSAGES OFF)
set(CMAKE_INSTALL_MESSAGE LAZY)

include_directories(tools common)

add_subdirectory(tools)
add_subdirectory(common)
add_subdirectory(sinus_seq)
add_subdirectory(sinus_omp_coarse_grain)
add_subdirectory(sinus_omp_fine_grain)
add_subdirectory(sinus_omp_adaptatif)
add_subdirectory(sinus_omp_tasks)
add_subdirectory(sinus_tbb)
