#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_circle_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Circle_2>& circle_2) {
  circle_2
    // Creation
    .CTOR(const Point_2&, const FT&)
    .CTOR(const Point_2&, const FT&, const CGAL::Orientation&)
    .CTOR(const Point_2&, const Point_2&, const Point_2&)
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Point_2&, const Point_2&, const CGAL::Orientation&)
    .CTOR(const Point_2&)
    .CTOR(const Point_2&, const CGAL::Orientation&)
    // Access Functions
    .METHOD(Circle_2, center        )
    .METHOD(Circle_2, squared_radius)
    .METHOD(Circle_2, orientation   )
    OVERRIDE_BASE(kernel, circle_2)
    .BINARY_OP_SELF(const Circle_2&, ==)
    UNSET_OVERRIDE(kernel, circle_2)
    // Predicates
    .METHOD(Circle_2, is_degenerate        )
    .METHOD(Circle_2, oriented_side        )
    .METHOD(Circle_2, bounded_side         )
    .METHOD(Circle_2, has_on_positive_side )
    .METHOD(Circle_2, has_on_negative_side )
    .METHOD(Circle_2, has_on_boundary      )
    .METHOD(Circle_2, has_on_bounded_side  )
    .METHOD(Circle_2, has_on_unbounded_side)
    // Miscellaneous
    .METHOD(Circle_2, opposite            )
    .METHOD(Circle_2, orthogonal_transform)
    .METHOD(Circle_2, bbox                )
    // Representation
    .REPR(Circle_2)
    ;
}

} // jlcgal
