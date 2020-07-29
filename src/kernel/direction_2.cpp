#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_direction_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Direction_2>& direction_2) {
  direction_2
    // Creation
    .CTOR(const Vector_2&)
    .CTOR(const Line_2&)
    .CTOR(const Ray_2&)
    .CTOR(const Segment_2&)
    .CTOR(const RT&, const RT&)
    // Operations
    .METHOD(Direction_2, delta)
    .METHOD(Direction_2, dx   )
    .METHOD(Direction_2, dy   )
    OVERRIDE_BASE(kernel, direction_2)
    .BINARY_OP_SELF(const Direction_2&, ==)
    .BINARY_OP_SELF(const Direction_2&,  <)
    .BINARY_OP_SELF(const Direction_2&,  >)
    .BINARY_OP_SELF(const Direction_2&, <=)
    .BINARY_OP_SELF(const Direction_2&, >=)
    .UNARY_OP(-, const Direction_2&)
    UNSET_OVERRIDE(kernel, direction_2)
    .METHOD(Direction_2, counterclockwise_in_between)
    // Miscellaneous
    .METHOD(Direction_2, vector   )
    .METHOD(Direction_2, transform)
    // Representation
    .REPR(Direction_2)
    ;
}

} // jlcgal
