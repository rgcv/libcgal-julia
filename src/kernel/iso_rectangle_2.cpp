#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_iso_rectangle_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Iso_rectangle_2>& iso_rectangle_2) {
  iso_rectangle_2
    // Creation
    .constructor<const Point_2&, const Point_2&>()
    .constructor<const Point_2&, const Point_2&, int>()
    .constructor<const Point_2&, const Point_2&, const Point_2&, const Point_2&>()
    .constructor<const RT&, const RT&, const RT&, const RT&>()
    .constructor<const RT&, const RT&, const RT&, const RT&, const RT&>()
    .constructor<const Bbox_2&>();
  kernel.set_override_module(jl_base_module);
  iso_rectangle_2
    // Operations
    .method("==",  &Iso_rectangle_2::operator==)
    .method("min", &Iso_rectangle_2::min)
    .method("max", &Iso_rectangle_2::max);
  kernel.unset_override_module();
  iso_rectangle_2
    .method("vertex",    &Iso_rectangle_2::vertex)
    .method("xmin",      &Iso_rectangle_2::xmin)
    .method("ymin",      &Iso_rectangle_2::ymin)
    .method("xmax",      &Iso_rectangle_2::xmax)
    .method("ymax",      &Iso_rectangle_2::ymax)
    .method("min_coord", &Iso_rectangle_2::min_coord)
    .method("max_coord", &Iso_rectangle_2::max_coord)
    // Predicates
    .method("is_degenerate",         &Iso_rectangle_2::is_degenerate)
    .method("bounded_side",          &Iso_rectangle_2::bounded_side)
    .method("has_on_boundary",       &Iso_rectangle_2::has_on_boundary)
    .method("has_on_bounded_side",   &Iso_rectangle_2::has_on_bounded_side)
    .method("has_on_unbounded_side", &Iso_rectangle_2::has_on_unbounded_side)
    // Miscellaneous
    .method("area",      &Iso_rectangle_2::area)
    .method("bbox",      &Iso_rectangle_2::bbox)
    .method("transform", &Iso_rectangle_2::transform)
    // Representation
    .TO_STRING(Iso_rectangle_2)
    ;
}

} // jlcgal
