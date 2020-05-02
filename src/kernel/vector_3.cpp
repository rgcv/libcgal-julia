#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

void wrap_vector_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Vector_3>& vector_3) {
  vector_3
    // Public member functions
    .METHOD(Vector_3, squared_length)
    OVERRIDE_BASE(kernel, vector_3)
    .BINARY_OP(const Vector_3&, *, const RT&      )
    .BINARY_OP(const RT&,       *, const Vector_3&)
    UNSET_OVERRIDE(kernel, vector_3)
    // Creation
    .CTOR(const Point_3&, const Point_3&)
    .CTOR(const Segment_3&)
    /* .CTOR(const Line_3&) */
    /* .CTOR(const Ray_3&) */
    .CTOR(const CGAL::Null_vector&)
    .CTOR(const RT&, const RT&, const RT&, const RT&)
    .CTOR(const FT&, const FT&, const FT&)
    // Coordinate access
    .METHOD(Vector_3, hx)
    .METHOD(Vector_3, hy)
    .METHOD(Vector_3, hz)
    .METHOD(Vector_3, hw)
    .METHOD(Vector_3, x )
    .METHOD(Vector_3, y )
    .METHOD(Vector_3, z )
    // Convenience operations
    .METHOD(Vector_3, homogeneous)
    .METHOD(Vector_3, cartesian  )
    .METHOD(Vector_3, dimension  )
    /* .METHOD(Vector_3, transform  ) */
    /* .METHOD(Point_3, direction   ) */
    OVERRIDE_BASE(kernel, vector_3)
    // Operators
    .BINARY_OP_SELF(const Vector_3&, ==)
    .BINARY_OP(const Vector_3&,          ==, const CGAL::Null_vector&)
    .BINARY_OP(const CGAL::Null_vector&, ==, const Vector_3&         )
    .BINARY_OP_SELF(const Vector_3&,  +)
    .BINARY_OP_SELF(const Vector_3&,  -)
    .UNARY_OP(-, const Vector_3&)
    /* .BINARY_OP(const Vector_3&, /, const RT&) */
    .method("/", &safe_division<Vector_3, RT>)
    .BINARY_OP_SELF(const Vector_3&,  *)
    UNSET_OVERRIDE(kernel, vector_3)
    // Representation
    .REPR(Vector_3)
    ;
}

