#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

void wrap_point_2(jlcxx::Module& kernel, jlcxx::TypeWrapper<Point_2>& point_2) {
  point_2
    OVERRIDE_BASE(kernel, point_2)
    // Related Functions
    .BINARY_OP_SELF(const Point_2&,  <)
    .BINARY_OP_SELF(const Point_2&,  >)
    .BINARY_OP_SELF(const Point_2&, <=)
    .BINARY_OP_SELF(const Point_2&, >=)
    .BINARY_OP_SELF(const Point_2&,  -)
    .BINARY_OP(const Point_2&,      -, const CGAL::Origin&)
    .BINARY_OP(const CGAL::Origin&, -, const Point_2&     )
    .BINARY_OP(const Point_2&,      +, const Vector_2&    )
    .BINARY_OP(const Point_2&,      -, const Vector_2&    )
    // Operations
    .BINARY_OP_SELF(const Point_2&, ==)
    .BINARY_OP(const Point_2&, ==, const CGAL::Origin&)
    UNSET_OVERRIDE(kernel, point_2)
    // Creation
    .CTOR(const CGAL::Origin&)
    .CTOR(const RT&, const RT&, const RT&)
    .CTOR(const FT&, const FT&) // in a Cartesian kernel, covers (RT, RT) ctor
    .CTOR(const Weighted_point_2&)
    // Coordinate Access
    .METHOD(Point_2, hx)
    .METHOD(Point_2, hy)
    .METHOD(Point_2, hw)
    .METHOD(Point_2, x )
    .METHOD(Point_2, y )
    // Convenience Operations
    .METHOD(Point_2, homogeneous)
    .METHOD(Point_2, cartesian  )
    // TODO: missing cartesian iterator methods
    .METHOD(Point_2, dimension)
    .METHOD(Point_2, bbox     )
    .METHOD(Point_2, transform)
    // Representation
    .REPR(Point_2)
    ;
}
