if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(CMAKE_INSTALL_MESSAGE LAZY)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

option(FLOAT "use simple/double numeric values for the computations" OFF)
if (FLOAT)
	add_definitions(-DFLOAT=1)
endif()

if (TIMERS)
	add_definitions(-DTIMERS=1)
endif()

list(APPEND CMAKE_MODULE_PATH "${communs_DIR}")
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL)
find_package(GLFW3)
find_package(GLEW)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if (OpenGL_FOUND AND GLFW3_FOUND AND GLEW_FOUND)
    set(USE_GRAPHICS On)
    add_compile_definitions(USE_GRAPHICS)
  else()
    set(USE_GRAPHICS Off)
    message(STATUS "OpenGL libraries not found, disable graphical interface")
  endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(USE_GRAPHICS Off)
  message(STATUS "Graphics option not available on windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(USE_GRAPHICS Off)
  message(STATUS "Graphics option not available on windows")
endif()

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${communs_DIR}/include
  )
