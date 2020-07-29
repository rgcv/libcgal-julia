#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_ray_2(jlcxx::Module& kernel, jlcxx::TypeWrapper<Ray_2>& ray_2) {
  ray_2
    // Creation
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Point_2&, const Direction_2&)
    .CTOR(const Point_2&, const Vector_2&)
    .CTOR(const Point_2&, const Line_2&)
    // Operations
    OVERRIDE_BASE(kernel, ray_2)
    .BINARY_OP_SELF(const Ray_2&, ==)
    UNSET_OVERRIDE(kernel, ray_2)
    .METHOD(Ray_2, source         )
    .METHOD(Ray_2, point          )
    .METHOD(Ray_2, direction      )
    .METHOD(Ray_2, to_vector      )
    .METHOD(Ray_2, supporting_line)
    .METHOD(Ray_2, opposite       )
    // Predicates
    .METHOD(Ray_2, is_degenerate   )
    .METHOD(Ray_2, is_horizontal   )
    .METHOD(Ray_2, is_vertical     )
    .METHOD(Ray_2, has_on          )
    .METHOD(Ray_2, collinear_has_on)
    // Miscellaneous
    .METHOD(Ray_2, transform)
    // Representation
    .REPR(Ray_2)
    ;
}

} // jlcgal
