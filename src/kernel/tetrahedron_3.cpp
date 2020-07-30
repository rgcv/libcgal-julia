#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_tetrahedron_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Tetrahedron_3>& tetrahedron_3) {
  tetrahedron_3
    // Creation
    .constructor<const Point_3&, const Point_3&, const Point_3&, const Point_3&>()
    ;
  kernel.set_override_module(jl_base_module);
  tetrahedron_3
    // Operations
    .method("==", &Tetrahedron_3::operator==)
    ;
  kernel.unset_override_module();
  tetrahedron_3
    .method("vertex", &Tetrahedron_3::vertex)
    // Predicates
    .method("is_degenerate",         &Tetrahedron_3::is_degenerate)
    .method("orientation",           &Tetrahedron_3::orientation)
    .method("oriented_side",         &Tetrahedron_3::oriented_side)
    .method("bounded_side",          &Tetrahedron_3::bounded_side)
    // Convenience Boolean Functions
    .method("has_on_positive_side",  &Tetrahedron_3::has_on_positive_side)
    .method("has_on_negative_side",  &Tetrahedron_3::has_on_negative_side)
    .method("has_on_boundary",       &Tetrahedron_3::has_on_boundary)
    .method("has_on_bounded_side",   &Tetrahedron_3::has_on_bounded_side)
    .method("has_on_unbounded_side", &Tetrahedron_3::has_on_unbounded_side)
    // Miscellaneous
    .method("volume",    &Tetrahedron_3::volume)
    .method("bbox",      &Tetrahedron_3::bbox)
    .method("transform", &Tetrahedron_3::transform)
    // Representation
    .TO_STRING(Tetrahedron_3)
    ;
}

} // jlcgal
