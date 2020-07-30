#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_plane_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Plane_3>& plane_3) {
  plane_3
    // Creation
    .constructor<const RT&, const RT&, const RT&, const RT&>()
    .constructor<const Point_3&, const Point_3&, const Point_3&>()
    .constructor<const Point_3&, const Vector_3&>()
    .constructor<const Point_3&, const Direction_3&>()
    .constructor<const Line_3&, const Point_3&>()
    .constructor<const Ray_3&, const Point_3&>()
    .constructor<const Segment_3&, const Point_3&>()
    .constructor<const Circle_3&>()
    ;
  kernel.set_override_module(jl_base_module);
  plane_3
    .method("==", [](const Plane_3& h1, const Plane_3& h2) { return h1 == h2; })
    ;
  kernel.unset_override_module();
  plane_3
    .method("a", &Plane_3::a)
    .method("b", &Plane_3::b)
    .method("c", &Plane_3::c)
    .method("d", &Plane_3::d)
    .method("perpendicular_line",   &Plane_3::perpendicular_line)
    .method("projection",           &Plane_3::projection)
    .method("opposite",             &Plane_3::opposite)
    .method("point",                &Plane_3::point)
    .method("orthogonal_vector",    &Plane_3::orthogonal_vector)
    .method("orthogonal_direction", &Plane_3::orthogonal_direction)
    .method("base1", &Plane_3::base1)
    .method("base2", &Plane_3::base2)
    // Conversion
    .method("to_2d", &Plane_3::to_2d)
    .method("to_3d", &Plane_3::to_3d)
    // Predicates
    .method("oriented_side", &Plane_3::oriented_side)
    // Convenience boolean functions
    .method("has_on", [](const Plane_3& h, const Point_3&  p) { return h.has_on(p); })
    .method("has_on", [](const Plane_3& h, const Line_3&   l) { return h.has_on(l); })
    .method("has_on", [](const Plane_3& h, const Circle_3& c) { return h.has_on(c); })
    .method("has_on_positive_side", &Plane_3::has_on_positive_side)
    .method("has_on_negative_side", &Plane_3::has_on_negative_side)
    .method("is_degenerate",        &Plane_3::is_degenerate)
    // Miscellaneous
    .method("transform", &Plane_3::transform)
    // Representation
    .TO_STRING(Plane_3)
    ;
}

} // jlcgal
