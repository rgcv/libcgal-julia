#include <CGAL/number_utils.h>

#include <jlcxx/module.hpp>

#include "macros.hpp"
#include "kernel.hpp"

typedef Kernel::FT NT;

void wrap_algebra(jlcxx::Module& cgal) {
  // missing functions that involve EuclideanRing concept:
  // div, div_mod, mod
  OVERRIDE_BASE(cgal,);
#ifdef JLCGAL_EXACT_CONSTRUCTIONS
  CGAL_GLOBAL_FUNCTION(NT, abs, const NT&);
  CGAL_GLOBAL_FUNCTION(NT, sqrt, const NT&);
  cgal.method("iszero", &CGAL::is_zero<NT>);
  cgal.method("isone", &CGAL::is_one<NT>);
  cgal.method("float", &CGAL::to_double<NT>);
#endif
  CGAL_GLOBAL_FUNCTION(CGAL::Sign, sign, const NT&);
  UNSET_OVERRIDE(cgal,);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare, const NT&, const NT&);
  CGAL_GLOBAL_FUNCTION(NT, integral_division, const NT&, const NT&);
  CGAL_GLOBAL_FUNCTION(NT, inverse, const NT&);
  CGAL_GLOBAL_FUNCTION(bool, is_negative, const NT&);
  CGAL_GLOBAL_FUNCTION(bool, is_positive, const NT&);
  CGAL_GLOBAL_FUNCTION(bool, is_square, const NT&);
  CGAL_GLOBAL_FUNCTION(bool, is_square, const NT&, NT&);
  // no matching method for given NT
  //GLOBAL_FUNCTION(void, simplify, const NT&);
  cgal.method("to_interval", [](const NT& nt) {
      auto pair = CGAL::to_interval(nt);
      return std::make_tuple(pair.first, pair.second);
  });
  CGAL_GLOBAL_FUNCTION(NT, unit_part, const NT&);
}
