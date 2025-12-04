cmake_minimum_required(VERSION 3.10)

project(ExempleTBB)

set(CMAKE_RULE_MESSAGES OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#find_package(TBB)

if (TBB_FOUND)
else()
  set(TBB_SRCDIR     "${CMAKE_BINARY_DIR}/oneTBB_src")
  set(TBB_BUILDDIR   "${CMAKE_BINARY_DIR}/oneTBB_build")
  set(TBB_INSTALLDIR "${CMAKE_INSTALL_PREFIX}/oneTBB")
  include(ExternalProject)
  ExternalProject_Add(LOCAL_TBB 
      GIT_REPOSITORY  https://github.com/uxlfoundation/oneTBB
      SOURCE_DIR      ${TBB_SRCDIR}
      CONFIGURE_COMMAND  ${CMAKE_COMMAND} -D TBB_TEST=OFF
                              -S ${TBB_SRCDIR} 
                              -B ${TBB_BUILDDIR}
                              --install-prefix ${TBB_INSTALLDIR}
      BUILD_COMMAND     ${CMAKE_COMMAND}
                              --build ${TBB_BUILDDIR}
      INSTALL_COMMAND    ${CMAKE_COMMAND}
                              --install ${TBB_BUILDDIR}
      )
  set(TBB_INCLUDE_DIR ${TBB_INSTALLDIR}/include)
  set(TBB_LIBRARY_DIRS ${TBB_INSTALLDIR}/lib ${TBB_INSTALLDIR}/lib64)
endif()

include_directories(tools ${TBB_INCLUDE_DIR})
add_subdirectory(tools)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

link_directories(
  ${TBB_LIBRARY_DIRS}
)

add_executable(
  exemple_par 
  main_par.cxx
  matrix.cxx
)

target_link_libraries(
  exemple_par tools tbb)

add_executable(
  exemple_seq 
  main_seq.cxx
  matrix.cxx
)

target_link_libraries(
  exemple_seq tools)
  
install(TARGETS exemple_seq exemple_par DESTINATION .)


