#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_line_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Line_3>& line_3) {
  line_3
    // Creation
    .CTOR(const Point_3&, const Point_3&)
    .CTOR(const Point_3&, const Direction_3&)
    .CTOR(const Point_3&, const Vector_3&)
    .CTOR(const Segment_3&)
    .CTOR(const Ray_3&)
    // Operations
    OVERRIDE_BASE(kernel, line_3)
    .BINARY_OP_SELF(const Line_3&, ==)
    UNSET_OVERRIDE(kernel, line_3)
    .METHOD(Line_3, projection)
    .UNAMBIG_METHOD(Point_3, Line_3, point, const FT)
    // Predicates
    .METHOD(Line_3, is_degenerate)
    .METHOD(Line_3, has_on       )
    // Miscellaneous
    .METHOD(Line_3, perpendicular_plane)
    .METHOD(Line_3, opposite           )
    .METHOD(Line_3, to_vector          )
    .METHOD(Line_3, direction          )
    .METHOD(Line_3, transform          )
    // Representation
    .REPR(Line_3)
    ;
}

} // jlcgal
