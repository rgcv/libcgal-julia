#include <CGAL/enum.h>

#include <jlcxx/module.hpp>

#include "jlcxx.hpp"

#include "enum.hpp"

#define CGAL_CONST(name) cgal.set_const(#name, CGAL::name)

void wrap_enum(jlcxx::Module& cgal) {
  jl_value_t *jl_cpp_enum = jlcxx::julia_type("CppEnum");

  cgal.add_bits<CGAL::Angle>("Angle", jl_cpp_enum);
  CGAL_CONST(OBTUSE); CGAL_CONST(RIGHT); CGAL_CONST(ACUTE);

  cgal.add_bits<CGAL::Bounded_side>("BoundedSide", jl_cpp_enum);
  CGAL_CONST(ON_UNBOUNDED_SIDE); CGAL_CONST(ON_BOUNDARY); CGAL_CONST(ON_BOUNDED_SIDE);

  // Box_parameter_space_2 is causing issues, skipping it

  cgal.add_bits<CGAL::Sign>("Sign", jl_cpp_enum);
  CGAL_CONST(NEGATIVE); CGAL_CONST(ZERO); CGAL_CONST(POSITIVE);

  // Orientation
  CGAL_CONST(LEFT_TURN); CGAL_CONST(RIGHT_TURN);
  CGAL_CONST(CLOCKWISE); CGAL_CONST(COUNTERCLOCKWISE);
  CGAL_CONST(COLLINEAR); CGAL_CONST(COPLANAR); CGAL_CONST(DEGENERATE);

  // Oriented_side
  CGAL_CONST(ON_NEGATIVE_SIDE); CGAL_CONST(ON_ORIENTED_BOUNDARY); CGAL_CONST(ON_POSITIVE_SIDE);

  // Comparison_result
  CGAL_CONST(SMALLER); CGAL_CONST(EQUAL); CGAL_CONST(LARGER);
}
