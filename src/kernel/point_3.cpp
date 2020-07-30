#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_point_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Point_3>& point_3) {
  kernel.set_override_module(jl_base_module);
  point_3
    // Creation
    .constructor<const CGAL::Origin&>()
    .constructor<const FT&, const FT&, const FT&>()
    .constructor<const RT&, const RT&, const RT&, const RT&>()
    .constructor<const Weighted_point_3&>()
    // Operations
    .method("==", [](const Point_3& p, const Point_3& q) { return p == q; })
    .method("==", [](const Point_3& p, const CGAL::Origin& o) { return p == o; })
    ;
  kernel.unset_override_module();
  point_3
    // Coordinate access
    .method("hx", &Point_3::hx)
    .method("hy", &Point_3::hy)
    .method("hz", &Point_3::hz)
    .method("hw", &Point_3::hw)
    .method("x",  &Point_3::x)
    .method("y",  &Point_3::y)
    .method("z",  &Point_3::z)
    // Convenience operators
    .method("homogeneous", &Point_3::homogeneous)
    .method("cartesian",   &Point_3::cartesian)
    .method("dimension",   &Point_3::dimension)
    .method("bbox",        &Point_3::bbox)
    .method("transform",   &Point_3::transform)
    // Representation
    .TO_STRING(Point_3)
    ;

  // Related Functions
  kernel.set_override_module(jl_base_module);
  kernel.method("<",  [](const Point_3& p, const Point_3& q) { return p <  q; });
  kernel.method(">",  [](const Point_3& p, const Point_3& q) { return p >  q; });
  kernel.method("<=", [](const Point_3& p, const Point_3& q) { return p <= q; });
  kernel.method(">=", [](const Point_3& p, const Point_3& q) { return p >= q; });
  kernel.method("-",  [](const Point_3& p, const Point_3& q) { return p -  q; });
  kernel.method("-",  [](const Point_3& p, const CGAL::Origin& o) { return p - o; });
  kernel.method("-",  [](const CGAL::Origin& o, const Point_3& p) { return o - p; });
  kernel.method("==", [](const CGAL::Origin& o, const Point_3& p) { return o == p; });
  kernel.unset_override_module();
}

} // jlcgal
