#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_direction_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Direction_2>& direction_2) {
  direction_2
    // Creation
    .constructor<const Vector_2&>()
    .constructor<const Line_2&>()
    .constructor<const Ray_2&>()
    .constructor<const Segment_2&>()
    .constructor<const RT&, const RT&>()
    // Operations
    .method("delta", &Direction_2::delta)
    .method("dx",    &Direction_2::dx)
    .method("dy",    &Direction_2::dy)
    ;
  kernel.set_override_module(jl_base_module);
  direction_2
    .method("==", &Direction_2::operator==)
    .method("<",  &Direction_2::operator<)
    .method(">",  &Direction_2::operator>)
    .method("<=", &Direction_2::operator<=)
    .method(">=", &Direction_2::operator>=)
    .method("-",  &Direction_2::operator-)
    ;
  kernel.unset_override_module();
  direction_2
    .method("counterclockwise_in_between", &Direction_2::counterclockwise_in_between)
    // Miscellaneous
    .method("vector",    &Direction_2::vector)
    .method("transform", &Direction_2::transform)
    // Representation
    .TO_STRING(Direction_2)
    ;
}

} // jlcgal
