#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_direction_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Direction_3>& direction_3) {
  direction_3
    // Creation
    .constructor<const Vector_3&>()
    .constructor<const Line_3&>()
    .constructor<const Ray_3&>()
    .constructor<const Segment_3&>()
    .constructor<const RT&, const RT&, const RT&>()
    // Operations
    .method("delta", &Direction_3::delta)
    .method("dx",    &Direction_3::dx)
    .method("dy",    &Direction_3::dy)
    ;
  kernel.set_override_module(jl_base_module);
  direction_3
    .method("==", &Direction_3::operator==)
    .method("-",  &Direction_3::operator-)
    ;
  kernel.unset_override_module();
  direction_3
    // Miscellaneous
    .method("vector",    &Direction_3::vector)
    .method("transform", &Direction_3::transform)
    // Representation
    .TO_STRING(Direction_3)
    ;
}

} // jlcgal
