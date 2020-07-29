#include <jlcxx/module.hpp>

namespace jlcgal {
  void wrap_origin(jlcxx::Module&);
  void wrap_enum(jlcxx::Module&);
  void wrap_kernel(jlcxx::Module&);
  void wrap_algebra(jlcxx::Module&);
  void wrap_global_kernel_functions(jlcxx::Module&);
  void wrap_convex_hull_2(jlcxx::Module&);
  void wrap_principal_component_analysis(jlcxx::Module&);
  void wrap_polygon_2(jlcxx::Module&);
  void wrap_triangulation_2(jlcxx::Module&);
  void wrap_voronoi_diagram_2(jlcxx::Module&);
} // jlcgal

JLCXX_MODULE define_julia_module(jlcxx::Module& cgal) {
  using namespace jlcgal;
  wrap_origin(cgal);
  wrap_enum(cgal);
  wrap_kernel(cgal);
  wrap_algebra(cgal);
  wrap_global_kernel_functions(cgal);
  wrap_convex_hull_2(cgal);
  wrap_principal_component_analysis(cgal);
  wrap_polygon_2(cgal);
  wrap_triangulation_2(cgal);
  wrap_voronoi_diagram_2(cgal);
}
