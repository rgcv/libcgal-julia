#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_aff_transformation_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Aff_transformation_2>& aff_transformation_2) {
  aff_transformation_2
    // Creation
    .constructor<const CGAL::Identity_transformation&>()
    .constructor<const CGAL::Translation&, const Vector_2&>()
    .constructor<const CGAL::Rotation&, const Direction_2&, const RT&>()
    .constructor<const CGAL::Rotation&, const Direction_2&, const RT&, const RT&>()
    .constructor<const CGAL::Rotation&, const RT&, const RT&>()
    .constructor<const CGAL::Rotation&, const RT&, const RT&, const RT&>()
    .constructor<const CGAL::Scaling&, const RT&>()
    .constructor<const CGAL::Scaling&, const RT&, const RT&>()
    .constructor<const CGAL::Reflection&, const Line_2&>()
    .constructor<const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&>()
    .constructor<const RT&, const RT&, const RT&,
                 const RT&, const RT&, const RT&, const RT&>()
    .constructor<const RT&, const RT&,
                 const RT&, const RT&>()
    .constructor<const RT&, const RT&,
                 const RT&, const RT&, const RT&>()
    // Operations
    .method("transform", static_cast<Point_2 (Aff_transformation_2::*)(const Point_2&) const>(&Aff_transformation_2::transform))
    .method("transform", static_cast<Vector_2 (Aff_transformation_2::*)(const Vector_2&) const>(&Aff_transformation_2::transform))
    .method("transform", static_cast<Direction_2 (Aff_transformation_2::*)(const Direction_2&) const>(&Aff_transformation_2::transform))
    .method("transform", static_cast<Line_2 (Aff_transformation_2::*)(const Line_2&) const>(&Aff_transformation_2::transform))
    .method(static_cast<Point_2 (Aff_transformation_2::*)(const Point_2&) const>(&Aff_transformation_2::operator()))
    .method(static_cast<Vector_2 (Aff_transformation_2::*)(const Vector_2&) const>(&Aff_transformation_2::operator()))
    .method(static_cast<Direction_2 (Aff_transformation_2::*)(const Direction_2&) const>(&Aff_transformation_2::operator()))
    .method(static_cast<Line_2 (Aff_transformation_2::*)(const Line_2&) const>(&Aff_transformation_2::operator()))
    ;
    // Miscellaneous
  kernel.set_override_module(jl_base_module);
  aff_transformation_2
    .method("*",  [](const Aff_transformation_2& t, const Aff_transformation_2& s) { return t *  s; })
    .method("==", [](const Aff_transformation_2& t, const Aff_transformation_2& s) { return t == s; })
    ;
  kernel.unset_override_module();
  aff_transformation_2
    .method("inverse",        &Aff_transformation_2::inverse)
    .method("is_even",        &Aff_transformation_2::is_even)
    .method("is_odd",         &Aff_transformation_2::is_odd)
    .method("is_scaling",     &Aff_transformation_2::is_scaling)
    .method("is_translation", &Aff_transformation_2::is_translation)
    .method("is_rotation",    &Aff_transformation_2::is_rotation)
    .method("is_reflection",  &Aff_transformation_2::is_reflection)
    // Matrix Entry Access
    .method("cartesian",   &Aff_transformation_2::cartesian)
    .method("m",           &Aff_transformation_2::m)
    .method("homogeneous", &Aff_transformation_2::homogeneous)
    .method("hm",          &Aff_transformation_2::hm)
    // Representation
    .TO_STRING(Aff_transformation_2)
    ;
}

} // jlcgal
