#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_point_2(jlcxx::Module& kernel, jlcxx::TypeWrapper<Point_2>& point_2) {
  kernel.set_override_module(jl_base_module);
  point_2
    // Operations
    .method("==", &Point_2::operator==)
    .method("==", [](const Point_2& p, const CGAL::Origin& o) { return p == o; })
    ;
  kernel.unset_override_module();
  point_2
    // Creation
    .constructor<const CGAL::Origin&>()
    .constructor<const RT&, const RT&, const RT&>()
    .constructor<const FT&, const FT&>() // in a Cartesian kernel, covers (RT, RT) ctor
    .constructor<const Weighted_point_2&>()
    // Coordinate Access
    .method("hx", &Point_2::hx)
    .method("hy", &Point_2::hy)
    .method("hw", &Point_2::hw)
    .method("x",  &Point_2::x)
    .method("y",  &Point_2::y)
    // Convenience Operations
    .method("homogeneous", &Point_2::homogeneous)
    .method("cartesian",   &Point_2::cartesian)
    // TODO: missing cartesian iterator methods
    .method("dimension", &Point_2::dimension)
    .method("bbox",      &Point_2::bbox)
    .method("transform", &Point_2::transform)
    // Representation
    .TO_STRING(Point_2)
    ;

  // Related Functions
  kernel.set_override_module(jl_base_module);
  kernel.method("<",  [](const Point_2& p, const Point_2& q) { return p <  q; });
  kernel.method(">",  [](const Point_2& p, const Point_2& q) { return p >  q; });
  kernel.method("<=", [](const Point_2& p, const Point_2& q) { return p <= q; });
  kernel.method(">=", [](const Point_2& p, const Point_2& q) { return p >= q; });
  kernel.method("-",  [](const Point_2& p, const Point_2& q) { return p -  q; });
  kernel.method("-",  [](const Point_2& p, const CGAL::Origin& o) { return p - o; });
  kernel.method("-",  [](const CGAL::Origin& o, const Point_2& p) { return o - p; });
  kernel.method("==", [](const CGAL::Origin& o, const Point_2& p) { return p == o; })
  kernel.unset_override_module();
}

} // jlcgal
