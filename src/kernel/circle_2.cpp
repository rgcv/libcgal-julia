#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_circle_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Circle_2>& circle_2) {
  circle_2
    // Creation
    .constructor<const Point_2&, const FT&>()
    .constructor<const Point_2&, const FT&, const CGAL::Orientation&>()
    .constructor<const Point_2&, const Point_2&, const Point_2&>()
    .constructor<const Point_2&, const Point_2&>()
    .constructor<const Point_2&, const Point_2&, const CGAL::Orientation&>()
    .constructor<const Point_2&>()
    .constructor<const Point_2&, const CGAL::Orientation&>()
    // Access Functions
    .method("center",         &Circle_2::center)
    .method("squared_radius", &Circle_2::squared_radius)
    .method("orientation",    &Circle_2::orientation)
    ;
  kernel.set_override_module(jl_base_module);
  circle_2
    .method("==", &Circle_2::operator==)
    ;
  kernel.unset_override_module();
  circle_2
    // Predicates
    .method("is_degenerate",         &Circle_2::is_degenerate)
    .method("oriented_side",         &Circle_2::oriented_side)
    .method("bounded_side",          &Circle_2::bounded_side)
    .method("has_on_positive_side",  &Circle_2::has_on_positive_side)
    .method("has_on_negative_side",  &Circle_2::has_on_negative_side)
    .method("has_on_boundary",       &Circle_2::has_on_boundary)
    .method("has_on_bounded_side",   &Circle_2::has_on_bounded_side)
    .method("has_on_unbounded_side", &Circle_2::has_on_unbounded_side)
    // Miscellaneous
    .method("opposite",             &Circle_2::opposite)
    .method("orthogonal_transform", &Circle_2::orthogonal_transform)
    .method("bbox",                 &Circle_2::bbox)
    // Representation
    .TO_STRING(Circle_2)
    ;
}

} // jlcgal
