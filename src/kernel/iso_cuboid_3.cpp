#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_iso_cuboid_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Iso_cuboid_3>& iso_cuboid_3) {
  iso_cuboid_3
    // Creation
    .constructor<const Point_3&, const Point_3&>()
    .constructor<const Point_3&, const Point_3&, int>()
    .constructor<const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&>()
    .constructor<const RT&, const RT&, const RT&, const RT&, const RT&, const RT&>()
    .constructor<const RT&, const RT&, const RT&, const RT&, const RT&, const RT&, const RT&>()
    .constructor<const Bbox_3&>()
    ;
  kernel.set_override_module(jl_base_module);
  iso_cuboid_3
    // Operations
    .method("==",  &Iso_cuboid_3::operator==)
    .method("min", &Iso_cuboid_3::min)
    .method("max", &Iso_cuboid_3::max)
    ;
  kernel.unset_override_module();
  iso_cuboid_3
    .method("vertex",    &Iso_cuboid_3::vertex)
    .method("xmin",      &Iso_cuboid_3::xmin)
    .method("ymin",      &Iso_cuboid_3::ymin)
    .method("zmin",      &Iso_cuboid_3::zmin)
    .method("xmax",      &Iso_cuboid_3::xmax)
    .method("ymax",      &Iso_cuboid_3::ymax)
    .method("zmax",      &Iso_cuboid_3::zmax)
    .method("min_coord", &Iso_cuboid_3::min_coord)
    .method("max_coord", &Iso_cuboid_3::max_coord)
    // Predicates
    .method("is_degenerate",         &Iso_cuboid_3::is_degenerate)
    .method("bounded_side",          &Iso_cuboid_3::bounded_side)
    .method("has_on_boundary",       &Iso_cuboid_3::has_on_boundary)
    .method("has_on_bounded_side",   &Iso_cuboid_3::has_on_bounded_side)
    .method("has_on_unbounded_side", &Iso_cuboid_3::has_on_unbounded_side)
    // Miscellaneous
    .method("volume",    &Iso_cuboid_3::volume)
    .method("bbox",      &Iso_cuboid_3::bbox)
    .method("transform", &Iso_cuboid_3::transform)
    // Representation
    .TO_STRING(Iso_cuboid_3)
    ;
}

} // jlcgal
