#include <jlcxx/jlcxx.hpp>

void wrap_origin(jlcxx::Module&);
void wrap_enum(jlcxx::Module&);
void wrap_kernel(jlcxx::Module&);
void wrap_global_functions(jlcxx::Module&);

JLCXX_MODULE define_julia_module(jlcxx::Module& cgal) {
  wrap_origin(cgal);
  wrap_enum(cgal);
  wrap_kernel(cgal);
  wrap_global_functions(cgal);
}
