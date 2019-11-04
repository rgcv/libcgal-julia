#include <CGAL/number_utils.h>

#include <jlcxx/jlcxx.hpp>

#include "jlcxx.hpp"

#include "macros.hpp"
#include "enum.hpp"

#include "algebra.hpp"

void wrap_algebra(jlcxx::Module& cgal) {
  // missing functions that involve EuclideanRing concept:
  // div, div_mod, mod
  GLOBAL_FUNCTION(NT, abs, const NT&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare, const NT&, const NT&);
  GLOBAL_FUNCTION(NT, integral_division, const NT&, const NT&);
  GLOBAL_FUNCTION(NT, inverse, const NT&);
  GLOBAL_FUNCTION(bool, is_negative, const NT&);
  GLOBAL_FUNCTION(bool, is_positive, const NT&);
  GLOBAL_FUNCTION(bool, is_square, const NT&);
  GLOBAL_FUNCTION(bool, is_square, const NT&, NT&);
  GLOBAL_FUNCTION(bool, is_zero, const NT&);
  GLOBAL_FUNCTION(CGAL::Sign, sign, const NT&);
  // no matching method for given NT
  //GLOBAL_FUNCTION(void, simplify, const NT&);
  GLOBAL_FUNCTION(NT, sqrt, const NT&);
  GLOBAL_FUNCTION(NT, square, const NT&);
  GLOBAL_FUNCTION(double, to_double, const NT&);
  cgal.method("to_interval", [](const NT& nt) {
      auto pair = CGAL::to_interval(nt);
      return std::make_tuple(pair.first, pair.second);
  });
  GLOBAL_FUNCTION(NT, unit_part, const NT&);
}
