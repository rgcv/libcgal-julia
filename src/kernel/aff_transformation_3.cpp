#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

template<typename T>
T
transform(const Aff_transformation_3& at, const T& t) {
  return at.transform(t);
}

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
    .method("transform", &transform<Point_3>)
    .method("transform", &transform<Vector_3>)
    .method("transform", &transform<Direction_3>)
    .method("transform", &transform<Plane_3>)
    .method(&transform<Point_3>)
    .method(&transform<Vector_3>)
    .method(&transform<Direction_3>)
    .method(&transform<Plane_3>)
    ;
    // Miscellaneous
  kernel.set_override_module(jl_base_module);
  aff_transformation_3
    .method("*",  &Aff_transformation_3::operator* )
    .method("==", &Aff_transformation_3::operator==)
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
    // See https://github.com/CGAL/cgal/issues/4698
    /* .TO_STRING(Aff_transformation_3) */
    ;
}

} // jlcgal
