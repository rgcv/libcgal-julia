#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_direction_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Direction_3>& direction_3) {
  direction_3
    // Creation
    .CTOR(const Vector_3&)
    .CTOR(const Line_3&)
    .CTOR(const Ray_3&)
    .CTOR(const Segment_3&)
    .CTOR(const RT&, const RT&, const RT&)
    // Operations
    .METHOD(Direction_3, delta)
    .METHOD(Direction_3, dx   )
    .METHOD(Direction_3, dy   )
    OVERRIDE_BASE(kernel, direction_3)
    .BINARY_OP_SELF(const Direction_3&, ==)
    .UNARY_OP(-, const Direction_3&)
    UNSET_OVERRIDE(kernel, direction_3)
    // Miscellaneous
    .METHOD(Direction_3, vector   )
    .METHOD(Direction_3, transform)
    // Representation
    .REPR(Direction_3)
    ;
}

} // jlcgal
