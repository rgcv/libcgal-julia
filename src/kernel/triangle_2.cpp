#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_triangle_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Triangle_2>& triangle_2) {
  triangle_2
    // Creation
    .CTOR(const Point_2&, const Point_2&, const Point_2&)
    // Operations
    OVERRIDE_BASE(kernel, triangle_2)
    .BINARY_OP_SELF(const Triangle_2&, ==)
    UNSET_OVERRIDE(kernel, triangle_2)
    .METHOD(Triangle_2, vertex)
    // Predicates
    .METHOD(Triangle_2, is_degenerate        )
    .METHOD(Triangle_2, orientation          )
    .METHOD(Triangle_2, oriented_side        )
    .METHOD(Triangle_2, bounded_side         )
    .METHOD(Triangle_2, has_on_positive_side )
    .METHOD(Triangle_2, has_on_negative_side )
    .METHOD(Triangle_2, has_on_boundary      )
    .METHOD(Triangle_2, has_on_bounded_side  )
    .METHOD(Triangle_2, has_on_unbounded_side)
    // Miscellaneous
    .METHOD(Triangle_2, opposite )
    .METHOD(Triangle_2, area     )
    .METHOD(Triangle_2, bbox     )
    .METHOD(Triangle_2, transform)
    // Representation
    .TO_STRING(Triangle_2)
    ;
}

} // jlcgal
