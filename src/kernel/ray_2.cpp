#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_ray_2(jlcxx::Module& kernel, jlcxx::TypeWrapper<Ray_2>& ray_2) {
  ray_2
    // Creation
    .constructor<const Point_2&, const Point_2&>()
    .constructor<const Point_2&, const Direction_2&>()
    .constructor<const Point_2&, const Vector_2&>()
    .constructor<const Point_2&, const Line_2&>()
    ;
  kernel.set_override_module(jl_base_module);
  ray_2
    // Operations
    .method("==", &Ray_2::operator==)
    ;
  kernel.unset_override_module();
  ray_2
    .method("source",          &Ray_2::source)
    .method("point",           &Ray_2::point)
    .method("direction",       &Ray_2::direction)
    .method("to_vector",       &Ray_2::to_vector)
    .method("supporting_line", &Ray_2::supporting_line)
    .method("opposite",        &Ray_2::opposite)
    // Predicates
    .method("is_degenerate",    &Ray_2::is_degenerate)
    .method("is_horizontal",    &Ray_2::is_horizontal)
    .method("is_vertical",      &Ray_2::is_vertical)
    .method("has_on",           &Ray_2::has_on)
    .method("collinear_has_on", &Ray_2::collinear_has_on)
    // Miscellaneous
    .method("transform", &Ray_2::transform)
    // Representation
    .TO_STRING(Ray_2)
    ;
}

} // jlcgal
