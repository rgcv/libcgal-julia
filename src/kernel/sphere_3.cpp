#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_sphere_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Sphere_3>& sphere_3) {
  sphere_3
    // Creation
    .constructor<const Point_3&, const FT&>()
    .constructor<const Point_3&, const FT&, const CGAL::Orientation&>()
    .constructor<const Point_3&, const Point_3&, const Point_3&, const Point_3&>()
    .constructor<const Point_3&, const Point_3&, const Point_3&>()
    .constructor<const Point_3&, const Point_3&, const Point_3&, const CGAL::Orientation&>()
    .constructor<const Point_3&, const Point_3&>()
    .constructor<const Point_3&, const Point_3&, const CGAL::Orientation&>()
    .constructor<const Point_3&>()
    .constructor<const Point_3&, const CGAL::Orientation&>()
    .constructor<const Circle_3&>()
    // Access Functions
    .method("center",         &Sphere_3::center)
    .method("squared_radius", &Sphere_3::squared_radius)
    .method("orientation",    &Sphere_3::orientation)
    ;
  kernel.set_override_module(jl_base_module);
  sphere_3
    .method("==", [](const Sphere_3& s1, const Sphere_3& s2) { return s1 == s2; })
    ;
  kernel.unset_override_module();
  sphere_3
    // Predicates
    .method("is_degenerate",         &Sphere_3::is_degenerate)
    .method("oriented_side",         &Sphere_3::oriented_side)
    .method("bounded_side",          &Sphere_3::bounded_side)
    .method("has_on_positive_side",  &Sphere_3::has_on_positive_side)
    .method("has_on_negative_side",  &Sphere_3::has_on_negative_side)
    .method("has_on_boundary",       &Sphere_3::has_on_boundary)
    .method("has_on_bounded_side",   &Sphere_3::has_on_bounded_side)
    .method("has_on_unbounded_side", &Sphere_3::has_on_unbounded_side)
    .method("has_on", [](const Sphere_3& s, const Point_3&  p) { return s.has_on(p); })
    .method("has_on", [](const Sphere_3& s, const Circle_3& c) { return s.has_on(c); })
    // Miscellaneous
    .method("opposite",             &Sphere_3::opposite)
    .method("orthogonal_transform", &Sphere_3::orthogonal_transform)
    .method("bbox",                 &Sphere_3::bbox)
    // Representation
    .TO_STRING(Sphere_3)
    ;
}

} // jlcgal
