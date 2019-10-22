#include <CGAL/enum.h>

#include <jlcxx/jlcxx.hpp>

#include <type_traits>

#include "enum.hpp"
#include "macros.hpp"

#define CGAL_CONST(name) cgal.set_const(#name, CGAL::name)

void wrap_enum(jlcxx::Module& cgal) {
  jl_value_t *jl_cpp_enum = jlcxx::julia_type("CppEnum");

  cgal.add_bits<CGAL::Angle>("Angle", jl_cpp_enum);
  CGAL_CONST(OBTUSE); CGAL_CONST(RIGHT); CGAL_CONST(ACUTE);

  cgal.add_bits<CGAL::Bounded_side>("BoundedSide");
  CGAL_CONST(ON_UNBOUNDED_SIDE); CGAL_CONST(ON_BOUNDARY); CGAL_CONST(ON_BOUNDED_SIDE);

  cgal.add_bits<CGAL::Box_parameter_space_2>("BoxParameterSpace2");
  CGAL_CONST(LEFT_BOUNDARY); CGAL_CONST(RIGHT_BOUNDARY);
  CGAL_CONST(BOTTOM_BOUNDARY); CGAL_CONST(TOP_BOUNDARY);
  CGAL_CONST(INTERIOR); CGAL_CONST(EXTERIOR);

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

  //GLOBAL_FUNCTION(CGAL::Oriented_side, opposite, const CGAL::Oriented_side&);
  //GLOBAL_FUNCTION(CGAL::Bounded_side, opposite,  const CGAL::Bounded_side&);
}
