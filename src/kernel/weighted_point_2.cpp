#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_weighted_point_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Weighted_point_2>& weighted_point_2) {
  weighted_point_2
    // Creation
    .CTOR(const CGAL::Origin&)
    .CTOR(const Point_2&)
    .CTOR(const Point_2&, const FT&)
    .CTOR(const FT&, const FT&)
    // Bare point and weight accessor
    .METHOD(Weighted_point_2, point )
    .METHOD(Weighted_point_2, weight)
    // Operations (delegated to underlying Point_2)
    OVERRIDE_BASE(kernel, weighted_point_2)
    .method("==", [](const Weighted_point_2& wp, const CGAL::Origin& o) {
      return wp.point() == o;
    })
    .BINARY_OP_SELF(const Weighted_point_2&, ==)
    .BINARY_OP_SELF(const Weighted_point_2&,  <)
    UNSET_OVERRIDE(kernel, weighted_point_2)
    // Coordinate Access
    .METHOD(Weighted_point_2, hx)
    .METHOD(Weighted_point_2, hy)
    .METHOD(Weighted_point_2, hw)
    .METHOD(Weighted_point_2, x )
    .METHOD(Weighted_point_2, y )
    // Convenience Operations
    .METHOD(Weighted_point_2, homogeneous)
    .METHOD(Weighted_point_2, cartesian  )
    .METHOD(Weighted_point_2, dimension  )
    .METHOD(Weighted_point_2, bbox       )
    .method("transform", [](const Weighted_point_2 &wp, const Aff_transformation_2 &t) {
        return Weighted_point_2(t.transform(wp.point()), wp.weight());
    })
    // Representation
    .TO_STRING(Weighted_point_2)
    ;
}

} // jlcgal
