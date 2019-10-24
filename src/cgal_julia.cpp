#include <jlcxx/jlcxx.hpp>

#include "origin.hpp"
#include "enum.hpp"
#include "kernel.hpp"
#include "global_kernel_functions.hpp"

JLCXX_MODULE define_julia_module(jlcxx::Module& cgal) {
  wrap_origin(cgal);
  wrap_enum(cgal);
  wrap_kernel(cgal);
  wrap_global_kernel_functions(cgal);
}
