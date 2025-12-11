cmake_minimum_required(VERSION 3.12)

set(VERSION Serial)
set(SYSTEM CPU_${VERSION})
set(code ncorps_${VERSION})

project(${VERSION})

include(${communs_DIR}/communs.cmake)

configure_file(${CMAKE_SOURCE_DIR}/../../main.cxx.in main_${VERSION}.cxx @ONLY)

add_executable(${code} main_${VERSION}.cxx system${SYSTEM}.cxx)

target_link_directories(${code} PUBLIC ${communs_DIR}/lib)
target_link_libraries(${code} PUBLIC communs 
   $<$<BOOL:${USE_GRAPHICS}>:GLFW::GLFW>
   $<$<BOOL:${USE_GRAPHICS}>:GLEW::GLEW>
   $<$<BOOL:${USE_GRAPHICS}>:OpenGL::OpenGL>
   )

install(TARGETS ${code} DESTINATION .)

