#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_line_2(jlcxx::Module& kernel, jlcxx::TypeWrapper<Line_2>& line_2) {
  line_2
    // Creation
    .CTOR(const RT&, const RT&, const RT&)
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Point_2&, const Direction_2&)
    .CTOR(const Point_2&, const Vector_2&)
    .CTOR(const Segment_2&)
    .CTOR(const Ray_2&)
    // Operators
    OVERRIDE_BASE(kernel, line_2)
    .BINARY_OP_SELF(const Line_2&, ==)
    UNSET_OVERRIDE(kernel, line_2)
    .METHOD(Line_2, a         )
    .METHOD(Line_2, b         )
    .METHOD(Line_2, c         )
    .UNAMBIG_METHOD(Point_2, Line_2, point, const FT&)
    .METHOD(Line_2, projection)
    .METHOD(Line_2, x_at_y    )
    .METHOD(Line_2, y_at_x    )
    // Predicates
    .METHOD(Line_2, is_degenerate)
    .METHOD(Line_2, is_horizontal)
    .METHOD(Line_2, is_vertical  )
    .METHOD(Line_2, oriented_side)
    // Convenience boolean functions
    .METHOD(Line_2, has_on              )
    .METHOD(Line_2, has_on_positive_side)
    .METHOD(Line_2, has_on_negative_side)
    // Miscellaneous
    .METHOD(Line_2, to_vector    )
    .METHOD(Line_2, direction    )
    .METHOD(Line_2, opposite     )
    .METHOD(Line_2, perpendicular)
    .METHOD(Line_2, transform    )
    // Representation
    .REPR(Line_2)
    ;
}

} // jlcgal
