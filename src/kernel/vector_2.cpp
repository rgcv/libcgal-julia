#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_vector_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Vector_2>& vector_2) {
  vector_2
    // Public Member Functions
    .METHOD(Vector_2, squared_length)
    OVERRIDE_BASE(kernel, vector_2)
    .BINARY_OP(const Vector_2&,     *, const RT&) // in Cartesian kernel, FT = RT
    .BINARY_OP(const RT&,           *, const Vector_2&) // ^ idem
    .BINARY_OP(const CGAL::Origin&, +, const Vector_2&)
    UNSET_OVERRIDE(kernel, vector_2)
    // Creation
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Segment_2&)
    .CTOR(const Ray_2&)
    .CTOR(const Line_2&)
    .CTOR(const CGAL::Null_vector&)
    .CTOR(const RT&, const RT&, const RT&)
    .CTOR(const FT&, const FT&)
    // Coordinate Access
    .METHOD(Vector_2, hx)
    .METHOD(Vector_2, hy)
    .METHOD(Vector_2, hw)
    .METHOD(Vector_2, x )
    .METHOD(Vector_2, y )
    // Convenience Operators
    .METHOD(Vector_2, homogeneous  )
    .METHOD(Vector_2, cartesian    )
    // TODO: missing cartesian iteratior methods
    .METHOD(Vector_2, dimension    )
    .METHOD(Vector_2, direction    )
    .METHOD(Vector_2, transform    )
    .METHOD(Vector_2, perpendicular)
    // Operators
    OVERRIDE_BASE(kernel, vector_2)
    .BINARY_OP_SELF(const Vector_2&, ==)
    .BINARY_OP(const Vector_2&,          ==, const CGAL::Null_vector&)
    .BINARY_OP(const CGAL::Null_vector&, ==, const Vector_2&         )
    .BINARY_OP_SELF(const Vector_2&,  +)
    .BINARY_OP_SELF(const Vector_2&,  -)
    .UNARY_OP(-, const Vector_2&)
    .BINARY_OP_SELF(const Vector_2&,  *)
    /* .BINARY_OP(const Vector_2&, /,  const RT&) */
    .method("/", &safe_division<Vector_2, RT>)
    UNSET_OVERRIDE(kernel, vector_2)
    // Representation
    .TO_STRING(Vector_2)
    ;
}

} // jlcgal
