set(code "sinus_tbb")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(TBB)

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

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

link_directories(
  ${TBB_LIBRARY_DIRS}
)

add_executable(${code}
  calcul.cxx 
  main.cxx
  parameters.cxx
)

target_link_libraries(${code}
   communs tools tbb)

install(TARGETS ${code} DESTINATION .)


