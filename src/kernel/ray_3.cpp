#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_ray_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Ray_3>& ray_3) {
  ray_3
    // Creation
    .constructor<const Point_3&, const Point_3&>()
    .constructor<const Point_3&, const Direction_3&>()
    .constructor<const Point_3&, const Vector_3&>()
    .constructor<const Point_3&, const Line_3&>()
    ;
  kernel.set_override_module(jl_base_module);
  ray_3
    // Operations
    .method("==", &Ray_3::operator==)
    ;
  kernel.unset_override_module();
  ray_3
    .method("source",          &Ray_3::source)
    .method("point",           &Ray_3::point)
    .method("direction",       &Ray_3::direction)
    .method("to_vector",       &Ray_3::to_vector)
    .method("supporting_line", &Ray_3::supporting_line)
    .method("opposite",        &Ray_3::opposite)
    .method("is_degenerate",    &Ray_3::is_degenerate)
    .method("has_on",           &Ray_3::has_on)
    .method("transform", &Ray_3::transform)
    // Representation
    .TO_STRING(Ray_3)
    ;
}

} // jlcgal
