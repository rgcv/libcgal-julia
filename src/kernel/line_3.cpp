#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_line_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Line_3>& line_3) {
  line_3
    // Creation
    .constructor<const Point_3&, const Point_3&>()
    .constructor<const Point_3&, const Direction_3&>()
    .constructor<const Point_3&, const Vector_3&>()
    .constructor<const Segment_3&>()
    .constructor<const Ray_3&>()
    ;
  kernel.set_override_module(jl_base_module);
  line_3
    // Operations
    .method("==", &Line_3::operator==)
    ;
  kernel.unset_override_module();
  line_3
    .method("projection", &Line_3::projection)
    .method("point", [](const Line_3& l, const FT& i) { return l.point(i); })
    // Predicates
    .method("is_degenerate", &Line_3::is_degenerate)
    .method("has_on",        &Line_3::has_on)
    // Miscellaneous
    .method("perpendicular_plane", &Line_3::perpendicular_plane)
    .method("opposite",            &Line_3::opposite)
    .method("to_vector",           &Line_3::to_vector)
    .method("direction",           &Line_3::direction)
    .method("transform",           &Line_3::transform)
    // Representation
    .TO_STRING(Line_3)
    ;
}

} // jlcgal
