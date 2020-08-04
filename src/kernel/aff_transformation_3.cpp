#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_aff_transformation_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Aff_transformation_3>& aff_transformation_3) {
  aff_transformation_3
    // Creation
    .constructor<const CGAL::Identity_transformation&>()
    .constructor<const CGAL::Translation&, const Vector_3&>()
    .constructor<const CGAL::Scaling&, const RT&>()
    .constructor<const CGAL::Scaling&, const RT&, const RT&>()
    .constructor<const RT&, const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&, const RT&>()
    .constructor<const RT&, const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&, const RT&, const RT&>()
    .constructor<const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&>()
    .constructor<const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&, const RT&>()
    // Operations
    .method("transform", static_cast<Point_3 (Aff_transformation_3::*)(const Point_3&) const>(&Aff_transformation_3::transform))
    .method("transform", static_cast<Vector_3 (Aff_transformation_3::*)(const Vector_3&) const>(&Aff_transformation_3::transform))
    .method("transform", static_cast<Direction_3 (Aff_transformation_3::*)(const Direction_3&) const>(&Aff_transformation_3::transform))
    .method("transform", static_cast<Plane_3 (Aff_transformation_3::*)(const Plane_3&) const>(&Aff_transformation_3::transform))
    .method(static_cast<Point_3 (Aff_transformation_3::*)(const Point_3&) const>(&Aff_transformation_3::operator()))
    .method(static_cast<Vector_3 (Aff_transformation_3::*)(const Vector_3&) const>(&Aff_transformation_3::operator()))
    .method(static_cast<Direction_3 (Aff_transformation_3::*)(const Direction_3&) const>(&Aff_transformation_3::operator()))
    .method(static_cast<Plane_3 (Aff_transformation_3::*)(const Plane_3&) const>(&Aff_transformation_3::operator()))
    ;
    // Miscellaneous
  kernel.set_override_module(jl_base_module);
  aff_transformation_3
    .method("*",  [](const Aff_transformation_3& t, const Aff_transformation_3& s) { return t *  s; })
    .method("==", [](const Aff_transformation_3& t, const Aff_transformation_3& s) { return t == s; })
    ;
  kernel.unset_override_module();
  aff_transformation_3
    .method("inverse", &Aff_transformation_3::inverse)
    .method("is_even", &Aff_transformation_3::is_even)
    .method("is_odd",  &Aff_transformation_3::is_odd )
    // Matrix Entry Access
    .method("cartesian",   &Aff_transformation_3::cartesian  )
    .method("m",           &Aff_transformation_3::m          )
    .method("homogeneous", &Aff_transformation_3::homogeneous)
    .method("hm",          &Aff_transformation_3::hm         )
    // Representation
    .TO_STRING(Aff_transformation_3)
    ;
}

} // jlcgal
