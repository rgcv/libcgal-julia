cmake_minimum_required(VERSION 3.1)

project(CGAL-julia)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## requirements
find_package(CGAL REQUIRED COMPONENTS Core)
add_definitions(-DCGAL_HEADER_ONLY=ON)
include(${CGAL_USE_FILE})

find_package(JlCxx)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

include_directories(${CGAL_INCLUDE_DIRS} ${Julia_INCLUDE_DIRS})
include_directories(include)
set(CGAL_JL_SOURCES
  src/origin.cpp
  src/enum.cpp
  src/algebra.cpp
  src/kernel.cpp
  src/global_kernel_functions.cpp
  src/voronoi_delaunay.cpp
  src/cgal_julia.cpp
)

add_library(cgal_julia_exact SHARED ${CGAL_JL_SOURCES})
target_compile_definitions(cgal_julia_exact PUBLIC JLCGAL_EXACT_CONSTRUCTIONS)
add_library(cgal_julia_inexact SHARED ${CGAL_JL_SOURCES})
target_link_libraries(cgal_julia_exact JlCxx::cxxwrap_julia ${CGAL_LIBRARIES})
target_link_libraries(cgal_julia_inexact JlCxx::cxxwrap_julia ${CGAL_LIBRARIES})
install(TARGETS
  cgal_julia_exact
  cgal_julia_inexact
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib)
