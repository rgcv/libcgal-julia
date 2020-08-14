add_subdirectory(kernel)
add_subdirectory(global_kernel_functions)

set(JLCGAL_SOURCES ${JLCGAL_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/algebra.cpp
  ${CMAKE_CURRENT_LIST_DIR}/cgal_julia.cpp
  ${CMAKE_CURRENT_LIST_DIR}/convex_hull_2.cpp
  ${CMAKE_CURRENT_LIST_DIR}/global_kernel_functions.cpp
  ${CMAKE_CURRENT_LIST_DIR}/kernel.cpp
  ${CMAKE_CURRENT_LIST_DIR}/polygon_2.cpp
  ${CMAKE_CURRENT_LIST_DIR}/principal_component_analysis.cpp
  ${CMAKE_CURRENT_LIST_DIR}/straight_skeleton_2.cpp
  ${CMAKE_CURRENT_LIST_DIR}/triangulation_2.cpp
  ${CMAKE_CURRENT_LIST_DIR}/voronoi_diagram_2.cpp
  PARENT_SCOPE)
