#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_aff_transformation_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Aff_transformation_3>& aff_transformation_3) {
  aff_transformation_3
    // Creation
    .CTOR(const CGAL::Identity_transformation&)
    .CTOR(const CGAL::Translation&, const Vector_3&)
    .CTOR(const CGAL::Scaling&, const RT&)
    .CTOR(const CGAL::Scaling&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&,
          const RT&, const RT&, const RT&, const RT&,
          const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&,
          const RT&, const RT&, const RT&, const RT&,
          const RT&, const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&,
          const RT&, const RT&, const RT&,
          const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&,
          const RT&, const RT&, const RT&,
          const RT&, const RT&, const RT&, const RT&)
    // Operations
    .UNAMBIG_METHOD(Point_3,     Aff_transformation_3, transform,  const Point_3&    )
    .UNAMBIG_METHOD(Vector_3,    Aff_transformation_3, transform,  const Vector_3&   )
    .UNAMBIG_METHOD(Direction_3, Aff_transformation_3, transform,  const Direction_3&)
    .UNAMBIG_METHOD(Plane_3,     Aff_transformation_3, transform,  const Plane_3&     )
    .INVOKE_METHOD(Point_3,      Aff_transformation_3, const Point_3&    )
    .INVOKE_METHOD(Vector_3,     Aff_transformation_3, const Vector_3&   )
    .INVOKE_METHOD(Direction_3,  Aff_transformation_3, const Direction_3&)
    .INVOKE_METHOD(Plane_3,      Aff_transformation_3, const Plane_3&     )
    // Miscellaneous
    OVERRIDE_BASE(kernel, aff_transformation_3)
    .BINARY_OP_SELF(const Aff_transformation_3&,  *)
    .BINARY_OP_SELF(const Aff_transformation_3&, ==)
    UNSET_OVERRIDE(kernel, aff_transformation_3)
    .METHOD(Aff_transformation_3, inverse)
    .METHOD(Aff_transformation_3, is_even)
    .METHOD(Aff_transformation_3, is_odd )
    // Matrix Entry Access
    .METHOD(Aff_transformation_3, cartesian  )
    .METHOD(Aff_transformation_3, m          )
    .METHOD(Aff_transformation_3, homogeneous)
    .METHOD(Aff_transformation_3, hm         )
    // Representation
    // See https://github.com/CGAL/cgal/issues/4698
    /* .TO_STRING(Aff_transformation_3) */
    ;
}

} // jlcgal
