#include <CGAL/aff_transformation_tags.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_aff_transformation_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Aff_transformation_2>& aff_transformation_2) {
  kernel.map_type<CGAL::Identity_transformation>("IdentityTransformation");
  kernel.map_type<CGAL::Reflection>("Reflection");
  kernel.map_type<CGAL::Rotation>("Rotation");
  kernel.map_type<CGAL::Scaling>("Scaling");
  kernel.map_type<CGAL::Translation>("Translation");

  aff_transformation_2
    // Creation
    .CTOR(const CGAL::Identity_transformation&)
    .CTOR(const CGAL::Translation&, const Vector_2&)
    .CTOR(const CGAL::Rotation&, const Direction_2&, const RT&)
    .CTOR(const CGAL::Rotation&, const Direction_2&, const RT&, const RT&)
    .CTOR(const CGAL::Rotation&, const RT&, const RT&)
    .CTOR(const CGAL::Rotation&, const RT&, const RT&, const RT&)
    .CTOR(const CGAL::Scaling&, const RT&)
    .CTOR(const CGAL::Scaling&, const RT&, const RT&)
    .CTOR(const CGAL::Reflection&, const Line_2&)
    .CTOR(const RT&, const RT&, const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&, const RT&)
    // Operations
    .UNAMBIG_METHOD(Point_2,     Aff_transformation_2, transform,  const Point_2&    )
    .UNAMBIG_METHOD(Vector_2,    Aff_transformation_2, transform,  const Vector_2&   )
    .UNAMBIG_METHOD(Direction_2, Aff_transformation_2, transform,  const Direction_2&)
    .UNAMBIG_METHOD(Line_2,      Aff_transformation_2, transform,  const Line_2&     )
    .INVOKE_METHOD(Point_2,      Aff_transformation_2, const Point_2&    )
    .INVOKE_METHOD(Vector_2,     Aff_transformation_2, const Vector_2&   )
    .INVOKE_METHOD(Direction_2,  Aff_transformation_2, const Direction_2&)
    .INVOKE_METHOD(Line_2,       Aff_transformation_2, const Line_2&     )
    // Miscellaneous
    OVERRIDE_BASE(kernel, aff_transformation_2)
    .BINARY_OP_SELF(const Aff_transformation_2&,  *)
    .BINARY_OP_SELF(const Aff_transformation_2&, ==)
    UNSET_OVERRIDE(kernel, aff_transformation_2)
    .METHOD(Aff_transformation_2, inverse)
    .METHOD(Aff_transformation_2, is_even)
    .METHOD(Aff_transformation_2, is_odd )
    // Matrix Entry Access
    .METHOD(Aff_transformation_2, cartesian  )
    .METHOD(Aff_transformation_2, m          )
    .METHOD(Aff_transformation_2, homogeneous)
    .METHOD(Aff_transformation_2, hm         )
    // Representation
    .REPR(Aff_transformation_2)
    ;
}

} // jlcgal
