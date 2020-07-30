#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_line_2(jlcxx::Module& kernel, jlcxx::TypeWrapper<Line_2>& line_2) {
  line_2
    // Creation
    .constructor<const RT&, const RT&, const RT&>()
    .constructor<const Point_2&, const Point_2&>()
    .constructor<const Point_2&, const Direction_2&>()
    .constructor<const Point_2&, const Vector_2&>()
    .constructor<const Segment_2&>()
    .constructor<const Ray_2&>()
    ;
  kernel.set_override_module(jl_base_module);
  line_2
    // Operators
    .method("==", &Line_2::operator==)
    ;
  kernel.unset_override_module();
  line_2
    .method("a", &Line_2::a)
    .method("b", &Line_2::b)
    .method("c", &Line_2::c)
    .method("point", [](const Line_2& l, const FT& i) { return l.point(i); })
    .method("projection", &Line_2::projection)
    .method("x_at_y",     &Line_2::x_at_y)
    .method("y_at_x",     &Line_2::y_at_x)
    // Predicates
    .method("is_degenerate", &Line_2::is_degenerate)
    .method("is_horizontal", &Line_2::is_horizontal)
    .method("is_vertical",   &Line_2::is_vertical)
    .method("oriented_side", &Line_2::oriented_side)
    // Convenience boolean functions
    .method("has_on",               &Line_2::has_on)
    .method("has_on_positive_side", &Line_2::has_on_positive_side)
    .method("has_on_negative_side", &Line_2::has_on_negative_side)
    // Miscellaneous
    .method("to_vector",     &Line_2::to_vector)
    .method("direction",     &Line_2::direction)
    .method("opposite",      &Line_2::opposite)
    .method("perpendicular", &Line_2::perpendicular)
    .method("transform",     &Line_2::transform)
    // Representation
    .TO_STRING(Line_2)
    ;
}

} // jlcgal
