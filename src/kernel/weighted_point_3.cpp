#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_weighted_point_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Weighted_point_3>& weighted_point_3) {
  weighted_point_3
    // Creation
    .constructor<const CGAL::Origin&>()
    .constructor<const Point_3&>()
    .constructor<const Point_3&, const FT&>()
    .constructor<const FT&, const FT&, const FT&>()
    // Bare point and weight accessor
    .method("point",  &Weighted_point_3::point)
    .method("weight", &Weighted_point_3::weight)
    ;
  kernel.set_override_module(jl_base_module);
  weighted_point_3
    // Operations (delegated to underlying Point_3)
    .method("==", [](const Weighted_point_3& p,  const CGAL::Origin& o) { return p.point() == o; })
    .method("==", [](const Weighted_point_3& wp, const Point_3& p) { return wp == p; })
    .method("==", [](const Weighted_point_3& p,  const Weighted_point_3& q) { return p == q; })
    .method("<",  [](const Weighted_point_3& p,  const Weighted_point_3& q) { return p <  q; })
    ;
  kernel.unset_override_module();
  weighted_point_3
    // Coordinate Access
    .method("hx", &Weighted_point_3::hx)
    .method("hy", &Weighted_point_3::hy)
    .method("hz", &Weighted_point_3::hz)
    .method("hw", &Weighted_point_3::hw)
    .method("x",  &Weighted_point_3::x)
    .method("y",  &Weighted_point_3::y)
    .method("z",  &Weighted_point_3::z)
    // Convenience Operations
    .method("homogeneous", &Weighted_point_3::homogeneous)
    .method("cartesian",   &Weighted_point_3::cartesian)
    .method("dimension",   &Weighted_point_3::dimension)
    .method("bbox",        &Weighted_point_3::bbox)
    .method("transform", [](const Weighted_point_3 &wp, const Aff_transformation_3 &t) {
      return Weighted_point_3(t.transform(wp.point()), wp.weight());
    })
    // Representation
    .TO_STRING(Weighted_point_3)
    ;

  kernel.set_override_module(jl_base_module);
  kernel.method(">",  [](const Weighted_point_3& p, const Weighted_point_3& q) { return q <  p; });
  kernel.method("<=", [](const Weighted_point_3& p, const Weighted_point_3& q) { return p <  q || p == q; });
  kernel.method(">=", [](const Weighted_point_3& p, const Weighted_point_3& q) { return q <  p || p == q; });
  kernel.method("-",  [](const Weighted_point_3& p, const CGAL::Origin& o) { return p.point() - o; });
  kernel.method("-",  [](const CGAL::Origin& o, const Weighted_point_3& p) { return o - p.point(); });
  kernel.method("==", [](const CGAL::Origin& o, const Weighted_point_3& p) { return p.point() == o; });
  kernel.method("==", [](const Point_3& p, const Weighted_point_3& q) { return q == p; });
  kernel.unset_override_module();
}

} // jlcgal
