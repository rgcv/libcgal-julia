#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_weighted_point_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Weighted_point_3>& weighted_point_3) {
  weighted_point_3
    // Creation
    .CTOR(const CGAL::Origin&)
    .CTOR(const Point_3&)
    .CTOR(const Point_3&, const FT&)
    .CTOR(const FT&, const FT&, const FT&)
    // Bare point and weight accessor
    .METHOD(Weighted_point_3, point )
    .METHOD(Weighted_point_3, weight)
    // Operations (delegated to underlying Point_3)
    OVERRIDE_BASE(kernel, weighted_point_3)
    .method("==", [](const Weighted_point_3& wp, const CGAL::Origin& o) {
      return wp.point() == o;
    })
    .BINARY_OP_SELF(const Weighted_point_3&, ==)
    .BINARY_OP_SELF(const Weighted_point_3&,  <)
    UNSET_OVERRIDE(kernel, weighted_point_3)
    // Coordinate Access
    .METHOD(Weighted_point_3, hx)
    .METHOD(Weighted_point_3, hy)
    .METHOD(Weighted_point_3, hz)
    .METHOD(Weighted_point_3, hw)
    .METHOD(Weighted_point_3, x )
    .METHOD(Weighted_point_3, y )
    .METHOD(Weighted_point_3, z )
    // Convenience Operations
    .METHOD(Weighted_point_3, homogeneous)
    .METHOD(Weighted_point_3, cartesian  )
    .METHOD(Weighted_point_3, dimension  )
    .METHOD(Weighted_point_3, bbox       )
    .method("transform", [](const Weighted_point_3 &wp, const Aff_transformation_3 &t) {
        return Weighted_point_3(t.transform(wp.point()), wp.weight());
    })
    // Representation
    .REPR(Weighted_point_3)
    ;
}

} // jlcgal
