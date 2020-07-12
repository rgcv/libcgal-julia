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

  src/kernel/aff_transformation_2.cpp
  src/kernel/bbox_2.cpp
  src/kernel/circle_2.cpp
  src/kernel/direction_2.cpp
  src/kernel/iso_rectangle_2.cpp
  src/kernel/line_2.cpp
  src/kernel/point_2.cpp
  src/kernel/ray_2.cpp
  src/kernel/segment_2.cpp
  src/kernel/triangle_2.cpp
  src/kernel/vector_2.cpp
  src/kernel/weighted_point_2.cpp

  src/kernel/circular_arc_2.cpp

  src/kernel/aff_transformation_3.cpp
  src/kernel/bbox_3.cpp
  src/kernel/circle_3.cpp
  src/kernel/direction_3.cpp
  src/kernel/iso_cuboid_3.cpp
  src/kernel/line_3.cpp
  src/kernel/plane_3.cpp
  src/kernel/point_3.cpp
  src/kernel/ray_3.cpp
  src/kernel/segment_3.cpp
  src/kernel/sphere_3.cpp
  src/kernel/tetrahedron_3.cpp
  src/kernel/triangle_3.cpp
  src/kernel/vector_3.cpp
  src/kernel/weighted_point_3.cpp

  src/kernel/circular_arc_3.cpp
 
  src/global_kernel_functions/global_lk_functions.cpp
  src/global_kernel_functions/global_ck_functions.cpp
  src/global_kernel_functions/global_sk_functions.cpp
  src/global_kernel_functions.cpp
  
  src/convex_hull_2.cpp
  src/principal_component_analysis.cpp
  src/polygon_2.cpp
  src/triangulation_2.cpp
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
