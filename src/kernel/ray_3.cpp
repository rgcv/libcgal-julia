#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

void wrap_ray_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Ray_3>& ray_3) {
  ray_3
    // Creation
    .CTOR(const Point_3&, const Point_3&)
    .CTOR(const Point_3&, const Direction_3&)
    .CTOR(const Point_3&, const Vector_3&)
    .CTOR(const Point_3&, const Line_3&)
    // Operations
    OVERRIDE_BASE(kernel, ray_3)
    .BINARY_OP_SELF(const Ray_3&, ==)
    UNSET_OVERRIDE(kernel, ray_3)
    .METHOD(Ray_3, source         )
    .METHOD(Ray_3, point          )
    .METHOD(Ray_3, direction      )
    .METHOD(Ray_3, to_vector      )
    .METHOD(Ray_3, supporting_line)
    .METHOD(Ray_3, opposite       )
    .METHOD(Ray_3, is_degenerate   )
    .METHOD(Ray_3, has_on          )
    .METHOD(Ray_3, transform)
    // Representation
    .REPR(Ray_3)
    ;
}

