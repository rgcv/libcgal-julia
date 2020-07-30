#include <CGAL/number_utils.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"

namespace jlcgal {

void wrap_algebra(jlcxx::Module& cgal) {
  typedef Kernel::FT NT;

  // missing functions that involve EuclideanRing concept:
  // div, div_mod, mod
#ifdef JLCGAL_EXACT_CONSTRUCTIONS
  cgal.set_override_module(jl_base_module);
  cgal.method("abs",    &CGAL::abs<NT>);
  cgal.method("sqrt",   &CGAL::sqrt<NT>);
  cgal.method("iszero", &CGAL::is_zero<NT>);
  cgal.method("isone",  &CGAL::is_one<NT>);
  cgal.method("float",  &CGAL::to_double<NT>);
  cgal.method("sign",   &CGAL::sign<NT>);
  cgal.unset_override_module();
#endif
  cgal.method("compare", &CGAL::compare<NT, NT>);
  cgal.method("integral_division", &CGAL::integral_division<NT, NT>);
  cgal.method("inverse", &CGAL::inverse<NT>);
  cgal.method("is_negative", &CGAL::is_negative<NT>);
  cgal.method("is_positive", &CGAL::is_positive<NT>);
  cgal.method("is_square", [](const NT& x) { return CGAL::is_square(x); });
  cgal.method("is_square", [](const NT& x, NT& y) { return CGAL::is_square(x, y); });
  cgal.method("to_interval", [](const NT& nt) {
    auto pair = CGAL::to_interval(nt);
    return std::make_tuple(pair.first, pair.second);
  });
  cgal.method("unit_part", &CGAL::unit_part<NT>);;
}

} // jlcgal
