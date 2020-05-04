#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

void wrap_plane_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Plane_3>& plane_3) {
  plane_3
    // Creation
    .CTOR(const RT&, const RT&, const RT&, const RT&)
    .CTOR(const Point_3&, const Point_3&, const Point_3&)
    .CTOR(const Point_3&, const Vector_3&)
    .CTOR(const Point_3&, const Direction_3&)
    .CTOR(const Line_3&, const Point_3&)
    .CTOR(const Ray_3&, const Point_3&)
    .CTOR(const Segment_3&, const Point_3&)
    .CTOR(const Circle_3&)
    OVERRIDE_BASE(kernel, plane_3)
    .BINARY_OP_SELF(const Plane_3&, ==)
    UNSET_OVERRIDE(kernel, plane_3)
    .METHOD(Plane_3, a)
    .METHOD(Plane_3, b)
    .METHOD(Plane_3, c)
    .METHOD(Plane_3, d)
    .METHOD(Plane_3, perpendicular_line)
    .METHOD(Plane_3, projection       )
    .METHOD(Plane_3, opposite         )
    .METHOD(Plane_3, point            )
    .METHOD(Plane_3, orthogonal_vector)
    .METHOD(Plane_3, orthogonal_direction)
    .METHOD(Plane_3, base1)
    .METHOD(Plane_3, base2)
    // Conversion
    .METHOD(Plane_3, to_2d)
    .METHOD(Plane_3, to_3d)
    // Predicates
    .METHOD(Plane_3, oriented_side)
    // Convenience boolean functions
    .UNAMBIG_METHOD(bool, Plane_3, has_on, const Point_3&)
    .UNAMBIG_METHOD(bool, Plane_3, has_on, const Line_3&)
    .UNAMBIG_METHOD(bool, Plane_3, has_on, const Circle_3&)
    .METHOD(Plane_3, has_on_positive_side)
    .METHOD(Plane_3, has_on_negative_side)
    .METHOD(Plane_3, is_degenerate       )
    // Miscellaneous
    .METHOD(Plane_3, transform)
    // Representation
    .REPR(Plane_3)
    ;
}
