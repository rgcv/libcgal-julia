#include <CGAL/aff_transformation_tags.h>

#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

template<typename T>
T
transform(const Aff_transformation_2& at, const T& t) {
  return at.transform(t);
}

void wrap_aff_transformation_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Aff_transformation_2>& aff_transformation_2) {
  kernel.map_type<CGAL::Identity_transformation>("IdentityTransformation");
  kernel.map_type<CGAL::Reflection>("Reflection");
  kernel.map_type<CGAL::Rotation>("Rotation");
  kernel.map_type<CGAL::Scaling>("Scaling");
  kernel.map_type<CGAL::Translation>("Translation");

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
    .method("transform", &transform<Point_2>)
    .method("transform", &transform<Vector_2>)
    .method("transform", &transform<Direction_2>)
    .method("transform", &transform<Line_2>)
    .method(&transform<Point_2>) // operator() overloads
    .method(&transform<Vector_2>)
    .method(&transform<Direction_2>)
    .method(&transform<Line_2>)
    ;
    // Miscellaneous
  kernel.set_override_module(jl_base_module);
  aff_transformation_2
    .method("*",  &Aff_transformation_2::operator*)
    .method("==", &Aff_transformation_2::operator==)
    ;
  kernel.unset_override_module();
  aff_transformation_2
    .method("inverse", &Aff_transformation_2::inverse)
    .method("is_even", &Aff_transformation_2::is_even)
    .method("is_odd",  &Aff_transformation_2::is_odd)
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
