#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_vector_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Vector_3>& vector_3) {
    // Public member functions
  vector_3
    .method("squared_length", &Vector_3::squared_length)
    // Creation
    .constructor<const Point_3&, const Point_3&>()
    .constructor<const Segment_3&>()
    .constructor<const Line_3&>()
    .constructor<const Ray_3&>()
    .constructor<const CGAL::Null_vector&>()
    .constructor<const RT&, const RT&, const RT&, const RT&>()
    .constructor<const FT&, const FT&, const FT&>()
    // Coordinate access
    .method("hx", &Vector_3::hx)
    .method("hy", &Vector_3::hy)
    .method("hz", &Vector_3::hz)
    .method("hw", &Vector_3::hw)
    .method("x",  &Vector_3::x)
    .method("y",  &Vector_3::y)
    .method("z",  &Vector_3::z)
    // Convenience operations
    .method("homogeneous", &Vector_3::homogeneous)
    .method("cartesian",   &Vector_3::cartesian)
    .method("dimension",   &Vector_3::dimension)
    .method("transform",   &Vector_3::transform)
    .method("direction",   &Vector_3::direction)
    ;
  kernel.set_override_module(jl_base_module);
  vector_3
    // Operators
    .method("+", &Vector_3::operator+)
    .method("-", [](const Vector_3& v) { return -v; })
    .method("-", [](const Vector_3& v, const Vector_3& u) { return v - u; })
    .method("*", [](const Vector_3& v, const Vector_3& u) { return v * u; })
    /* .BINARY_OP(const Vector_3&, /, const RT&) */
    .method("/", &safe_division<Vector_3, RT>)
    ;
  kernel.unset_override_module();
  vector_3
    // Representation
    .TO_STRING(Vector_3)
    ;

  kernel.set_override_module(jl_base_module);
  kernel.method("*", [](const Vector_3& v, const RT& x) { return v * x; }); // in Cartesian kernel, FT = RT
  kernel.method("*", [](const RT& x, const Vector_3& v) { return x * v; }); // ^ idem
  kernel.method("+", [](const CGAL::Origin& o, const Vector_3& v) { return o + v; });
  kernel.method("+", [](const Point_3& p,      const Vector_3& v) { return p + v; });
  kernel.method("-", [](const Point_3& p,      const Vector_3& v) { return p - v; });
  kernel.method("==", [](const Vector_3& v, const Vector_3& u) { return v == u; });
  kernel.method("==", [](const Vector_3& v, const CGAL::Null_vector& n) { return v == n; });
  kernel.method("==", [](const CGAL::Null_vector& n, const Vector_3& v) { return n == v; });
  kernel.unset_override_module();
}

} // jlcgal
