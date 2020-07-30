#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_triangle_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Triangle_3>& triangle_3) {
  triangle_3
    // Creation
    .constructor<const Point_3&, const Point_3&, const Point_3&>()
    ;
  kernel.set_override_module(jl_base_module);
  triangle_3
    // Operations
    .method("==", &Triangle_3::operator==)
    ;
  kernel.unset_override_module();
  triangle_3
    .method("vertex",           &Triangle_3::vertex)
    .method("supporting_plane", &Triangle_3::supporting_plane)
    // Predicates
    .method("is_degenerate", &Triangle_3::is_degenerate)
    .method("has_on",        &Triangle_3::has_on)
    // Miscellaneous
    .method("squared_area", &Triangle_3::squared_area)
    .method("bbox",         &Triangle_3::bbox)
    .method("transform",    &Triangle_3::transform)
    // Representation
    .TO_STRING(Triangle_3)
    ;
}

} // jlcgal
