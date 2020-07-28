project(JlCGAL)

cmake_minimum_required(VERSION 3.1)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

find_package(CGAL REQUIRED COMPONENTS Core)
include(${CGAL_USE_FILE})

find_package(JlCxx REQUIRED)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

include_directories(include)
file(GLOB_RECURSE JLCGAL_SOURCES src *.cpp)

add_library(cgal_julia_exact   SHARED ${JLCGAL_SOURCES})
add_library(cgal_julia_inexact SHARED ${JLCGAL_SOURCES})
target_compile_definitions(cgal_julia_exact PUBLIC JLCGAL_EXACT_CONSTRUCTIONS)
target_link_libraries(cgal_julia_exact   JlCxx::cxxwrap_julia ${CGAL_LIBRARIES})
target_link_libraries(cgal_julia_inexact JlCxx::cxxwrap_julia ${CGAL_LIBRARIES})

install(TARGETS
  cgal_julia_exact
  cgal_julia_inexact
ARCHIVE DESTINATION lib
LIBRARY DESTINATION lib
RUNTIME DESTINATION bin)
