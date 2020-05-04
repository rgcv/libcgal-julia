#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

void wrap_sphere_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Sphere_3>& sphere_3) {
  sphere_3
    // Creation
    .CTOR(const Point_3&, const FT&)
    .CTOR(const Point_3&, const FT&, const CGAL::Orientation&)
    .CTOR(const Point_3&, const Point_3&, const Point_3&, const Point_3&)
    .CTOR(const Point_3&, const Point_3&, const Point_3&)
    .CTOR(const Point_3&, const Point_3&, const Point_3&, const CGAL::Orientation&)
    .CTOR(const Point_3&, const Point_3&)
    .CTOR(const Point_3&, const Point_3&, const CGAL::Orientation&)
    .CTOR(const Point_3&)
    .CTOR(const Point_3&, const CGAL::Orientation&)
    .CTOR(const Circle_3&)
    // Access Functions
    .METHOD(Sphere_3, center        )
    .METHOD(Sphere_3, squared_radius)
    .METHOD(Sphere_3, orientation   )
    OVERRIDE_BASE(kernel, sphere_3)
    .BINARY_OP_SELF(const Sphere_3&, ==)
    UNSET_OVERRIDE(kernel, sphere_3)
    // Predicates
    .METHOD(Sphere_3, is_degenerate        )
    .METHOD(Sphere_3, oriented_side        )
    .METHOD(Sphere_3, bounded_side         )
    .METHOD(Sphere_3, has_on_positive_side )
    .METHOD(Sphere_3, has_on_negative_side )
    .METHOD(Sphere_3, has_on_boundary      )
    .METHOD(Sphere_3, has_on_bounded_side  )
    .METHOD(Sphere_3, has_on_unbounded_side)
    .UNAMBIG_METHOD(bool, Sphere_3, has_on, const Point_3&)
    .UNAMBIG_METHOD(bool, Sphere_3, has_on, const Circle_3&)
    // Miscellaneous
    .METHOD(Sphere_3, opposite            )
    .METHOD(Sphere_3, orthogonal_transform)
    .METHOD(Sphere_3, bbox                )
    // Representation
    .REPR(Sphere_3)
    ;
}
