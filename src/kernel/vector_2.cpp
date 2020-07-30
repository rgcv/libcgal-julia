#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_vector_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Vector_2>& vector_2) {
  vector_2
    // Public Member Functions
    .method("squared_length", &Vector_2::squared_length)
    // Creation
    .constructor<const Point_2&, const Point_2&>()
    .constructor<const Segment_2&>()
    .constructor<const Ray_2&>()
    .constructor<const Line_2&>()
    .constructor<const CGAL::Null_vector&>()
    .constructor<const RT&, const RT&, const RT&>()
    .constructor<const FT&, const FT&>()
    // Coordinate Access
    .method("hx", &Vector_2::hx)
    .method("hy", &Vector_2::hy)
    .method("hw", &Vector_2::hw)
    .method("x",  &Vector_2::x)
    .method("y",  &Vector_2::y)
    // Convenience Operators
    .method("homogeneous",   &Vector_2::homogeneous)
    .method("cartesian",     &Vector_2::cartesian)
    // TODO: missing cartesian iteratior methods
    .method("dimension",     &Vector_2::dimension)
    .method("direction",     &Vector_2::direction)
    .method("transform",     &Vector_2::transform)
    .method("perpendicular", &Vector_2::perpendicular)
    ;
  kernel.set_override_module(jl_base_module);
  vector_2
    // Operators
    .method("+", &Vector_2::operator+)
    .method("-", [](const Vector_2& v) { return -v; })
    .method("-", [](const Vector_2& v, const Vector_2& u) { return v - u; })
    .method("*", [](const Vector_2& v, const Vector_2& u) { return v * u; })
    /* .BINARY_OP(const Vector_2&, /,  const RT&) */
    .method("/", &safe_division<Vector_2, RT>)
    ;
  kernel.unset_override_module();
  vector_2
    // Representation
    .TO_STRING(Vector_2)
    ;

  kernel.set_override_module(jl_base_module);
  kernel.method("*", [](const Vector_2& v, const RT& x) { return v * x; }); // in Cartesian kernel, FT = RT
  kernel.method("*", [](const RT& x, const Vector_2& v) { return x * v; }); // ^ idem
  kernel.method("+", [](const CGAL::Origin& o, const Vector_2& v) { return o + v; });
  kernel.method("+", [](const Point_2& p,      const Vector_2& v) { return p + v; });
  kernel.method("-", [](const Point_2& p,      const Vector_2& v) { return p - v; });
  kernel.method("==", [](const Vector_2& v, const Vector_2& u) { return v == u; });
  kernel.method("==", [](const Vector_2& v, const CGAL::Null_vector& n) { return v == n; });
  kernel.method("==", [](const CGAL::Null_vector& n, const Vector_2& v) { return n == v; });
  kernel.unset_override_module();
}

} // jlcgal
