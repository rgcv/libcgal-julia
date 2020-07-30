#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_circle_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Circle_3>& circle_3) {
  circle_3
    // Creation
    .constructor<const Point_3&, const FT&, const Plane_3&>()
    .constructor<const Point_3&, const FT&, const Vector_3&>()
    .constructor<const Point_3&, const Point_3&, Point_3>()
    .constructor<const Sphere_3&, const Sphere_3&>()
    .constructor<const Sphere_3&, const Plane_3&>()
    .constructor<const Plane_3&, const Sphere_3&>()
    // Access Functions
    .method("center", &Circle_3::center)
    .method("squared_radius", &Circle_3::squared_radius)
    .method("supporting_plane", &Circle_3::supporting_plane)
    .method("diametral_sphere", &Circle_3::diametral_sphere)
    .method("area_divided_by_pi", &Circle_3::area_divided_by_pi)
    .method("approximate_area",&Circle_3::approximate_area)
    .method("squared_length_divided_by_pi_square", &Circle_3::squared_length_divided_by_pi_square)
    .method("approximate_squared_length", &Circle_3::approximate_squared_length)
    ;
  kernel.set_override_module(jl_base_module);
  circle_3
    .method("==", [](const Circle_3& p, const Circle_3& q) { return p == q; })
    ;
  kernel.unset_override_module();
  circle_3
    // Predicates
    .method("has_on", &Circle_3::has_on)
    // Miscellaneous
    .method("bbox", &Circle_3::bbox)
    // Representation
    .TO_STRING(Circle_3)
    ;
}

} // jlcgal
