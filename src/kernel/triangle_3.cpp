#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_triangle_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Triangle_3>& triangle_3) {
  triangle_3
    // Creation
    .CTOR(const Point_3&, const Point_3&, const Point_3&)
    // Operations
    OVERRIDE_BASE(kernel, triangle_3)
    .BINARY_OP_SELF(const Triangle_3&, ==)
    UNSET_OVERRIDE(kernel, triangle_3)
    .METHOD(Triangle_3, vertex          )
    .METHOD(Triangle_3, supporting_plane)
    // Predicates
    .METHOD(Triangle_3, is_degenerate)
    .METHOD(Triangle_3, has_on       )
    // Miscellaneous
    .METHOD(Triangle_3, squared_area)
    .METHOD(Triangle_3, bbox        )
    .METHOD(Triangle_3, transform   )
    // Representation
    .REPR(Triangle_3)
    ;
}

} // jlcgal
