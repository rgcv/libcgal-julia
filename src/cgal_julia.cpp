#include <jlcxx/jlcxx.hpp>

void wrap_kernel(jlcxx::Module&);

JLCXX_MODULE define_julia_module(jlcxx::Module& cgal) {
  wrap_kernel(cgal);
}
