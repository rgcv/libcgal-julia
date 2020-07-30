#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_circle_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Circle_3>& circle_3) {
  circle_3
    // Creation
    .CTOR(const Point_3&, const FT&, const Plane_3&)
    .CTOR(const Point_3&, const FT&, const Vector_3&)
    .CTOR(const Point_3&, const Point_3&, Point_3)
    .CTOR(const Sphere_3&, const Sphere_3&)
    .CTOR(const Sphere_3&, const Plane_3&)
    .CTOR(const Plane_3&, const Sphere_3&)
    // Access Functions
    .METHOD(Circle_3, center                             )
    .METHOD(Circle_3, squared_radius                     )
    .METHOD(Circle_3, supporting_plane                   )
    .METHOD(Circle_3, diametral_sphere                   )
    .METHOD(Circle_3, area_divided_by_pi                 )
    .METHOD(Circle_3, approximate_area                   )
    .METHOD(Circle_3, squared_length_divided_by_pi_square)
    .METHOD(Circle_3, approximate_squared_length         )
    OVERRIDE_BASE(kernel, circle_3)
    .BINARY_OP_SELF(const Circle_3&, ==)
    UNSET_OVERRIDE(kernel, circle_3)
    // Predicates
    .METHOD(Circle_3, has_on)
    // Miscellaneous
    .METHOD(Circle_3, bbox)
    // Representation
    .TO_STRING(Circle_3)
    ;
}

} // jlcgal
