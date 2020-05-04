#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

void wrap_point_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Point_3>& point_3) {
  point_3
    OVERRIDE_BASE(kernel, point_3)
    // Related functions
    .BINARY_OP_SELF(const Point_3&,  <)
    .BINARY_OP_SELF(const Point_3&,  >)
    .BINARY_OP_SELF(const Point_3&, <=)
    .BINARY_OP_SELF(const Point_3&, >=)
    .BINARY_OP_SELF(const Point_3&,  -)
    .BINARY_OP(const Point_3&,      -, const CGAL::Origin&)
    .BINARY_OP(const CGAL::Origin&, -, const Point_3&     )
    .BINARY_OP(const Point_3&,      +, const Vector_3&    )
    .BINARY_OP(const Point_3&,      -, const Vector_3&    )
    // Creation
    .CTOR(const CGAL::Origin&)
    .CTOR(const FT&, const FT&, const FT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&)
    .CTOR(const Weighted_point_3&)
    // Operations
    .BINARY_OP_SELF(const Point_3&, ==)
    .BINARY_OP(const Point_3&, ==, const CGAL::Origin&)
    UNSET_OVERRIDE(kernel, point_3)
    // Coordinate access
    .METHOD(Point_3, hx)
    .METHOD(Point_3, hy)
    .METHOD(Point_3, hz)
    .METHOD(Point_3, hw)
    .METHOD(Point_3, x )
    .METHOD(Point_3, y )
    .METHOD(Point_3, z )
    // Convenience operators
    .METHOD(Point_3, homogeneous)
    .METHOD(Point_3, cartesian  )
    .METHOD(Point_3, dimension  )
    .METHOD(Point_3, bbox       )
    .METHOD(Point_3, transform  )
    // Representation
    .REPR(Point_3)
    ;
}
