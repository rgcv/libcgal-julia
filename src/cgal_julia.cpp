#include <jlcxx/module.hpp>

void wrap_origin(jlcxx::Module&);
void wrap_enum(jlcxx::Module&);
void wrap_kernel(jlcxx::Module&);
void wrap_algebra(jlcxx::Module&);
void wrap_global_kernel_functions(jlcxx::Module&);
void wrap_triangulation_2(jlcxx::Module&);
void wrap_voronoi_delaunay(jlcxx::Module&);

JLCXX_MODULE define_julia_module(jlcxx::Module& cgal) {
  wrap_origin(cgal);
  wrap_enum(cgal);
  wrap_kernel(cgal);
  wrap_algebra(cgal);
  wrap_global_kernel_functions(cgal);
  wrap_triangulation_2(cgal);
  wrap_voronoi_delaunay(cgal);
}
