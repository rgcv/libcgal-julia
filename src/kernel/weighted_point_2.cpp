#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_weighted_point_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Weighted_point_2>& weighted_point_2) {
  weighted_point_2
    // Creation
    .constructor<const CGAL::Origin&>()
    .constructor<const Point_2&>()
    .constructor<const Point_2&, const FT&>()
    .constructor<const FT&, const FT&>()
    // Bare point and weight accessor
    .method("point",  &Weighted_point_2::point)
    .method("weight", &Weighted_point_2::weight)
    ;
  kernel.set_override_module(jl_base_module);
  weighted_point_2
    // Operations (delegated to underlying Point_2)
    .method("==", [](const Weighted_point_2& wp, const CGAL::Origin& o) { return o == wp; })
    .method("==", [](const Weighted_point_2& wp, const Point_2& p) { return wp == p; })
    .method("==", [](const Weighted_point_2& p, const Weighted_point_2& q) { return p == q; })
    .method("<",  [](const Weighted_point_2& p, const Weighted_point_2& q) { return p <  q; })
    ;
  kernel.unset_override_module();
  weighted_point_2
    // Coordinate Access
    .method("hx", &Weighted_point_2::hx)
    .method("hy", &Weighted_point_2::hy)
    .method("hw", &Weighted_point_2::hw)
    .method("x",  &Weighted_point_2::x)
    .method("y",  &Weighted_point_2::y)
    // Convenience Operations
    .method("homogeneous", &Weighted_point_2::homogeneous)
    .method("cartesian",   &Weighted_point_2::cartesian)
    .method("dimension",   &Weighted_point_2::dimension)
    .method("bbox",        &Weighted_point_2::bbox)
    .method("transform", [](const Weighted_point_2 &wp, const Aff_transformation_2 &t) {
      return Weighted_point_2(t.transform(wp.point()), wp.weight());
    })
    // Representation
    .TO_STRING(Weighted_point_2)
    ;

  kernel.set_override_module(jl_base_module);
  kernel.method(">",  [](const Weighted_point_2& p, const Weighted_point_2& q) { return q <  p; });
  kernel.method("<=", [](const Weighted_point_2& p, const Weighted_point_2& q) { return p <  q || p == q; });
  kernel.method(">=", [](const Weighted_point_2& p, const Weighted_point_2& q) { return q <  p || p == q; });
  kernel.method("-",  [](const Weighted_point_2& p, const CGAL::Origin& o) { return p.point() - o; });
  kernel.method("-",  [](const CGAL::Origin& o, const Weighted_point_2& p) { return o - p.point(); });
  kernel.method("==", [](const CGAL::Origin& o, const Weighted_point_2& p) { return o == p; });
  kernel.method("==", [](const Point_2& p, const Weighted_point_2& q) { return q == p; });
  kernel.unset_override_module();
}

} // jlcgal
