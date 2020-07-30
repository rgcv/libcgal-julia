#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_triangle_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Triangle_2>& triangle_2) {
  triangle_2
    // Creation
    .constructor<const Point_2&, const Point_2&, const Point_2&>()
    ;
  kernel.set_override_module(jl_base_module);
  triangle_2
    // Operations
    .method("==", &Triangle_2::operator==)
    ;
  kernel.unset_override_module();
  triangle_2
    .method("vertex", &Triangle_2::vertex)
    // Predicates
    .method("is_degenerate",         &Triangle_2::is_degenerate)
    .method("orientation",           &Triangle_2::orientation)
    .method("oriented_side",         &Triangle_2::oriented_side)
    .method("bounded_side",          &Triangle_2::bounded_side)
    .method("has_on_positive_side",  &Triangle_2::has_on_positive_side)
    .method("has_on_negative_side",  &Triangle_2::has_on_negative_side)
    .method("has_on_boundary",       &Triangle_2::has_on_boundary)
    .method("has_on_bounded_side",   &Triangle_2::has_on_bounded_side)
    .method("has_on_unbounded_side", &Triangle_2::has_on_unbounded_side)
    // Miscellaneous
    .method("opposite",  &Triangle_2::opposite)
    .method("area",      &Triangle_2::area)
    .method("bbox",      &Triangle_2::bbox)
    .method("transform", &Triangle_2::transform)
    // Representation
    .TO_STRING(Triangle_2)
    ;
}

} // jlcgal
