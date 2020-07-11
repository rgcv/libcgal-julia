#include <string>
#include <sstream>

#include <CGAL/IO/io.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "kernel_conversion.hpp"
#include "macros.hpp"

void wrap_circular_arc_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Circular_arc_3>& circular_arc_3) {
  const std::string name = jlcxx::julia_type_name(circular_arc_3.dt());
  circular_arc_3
    // Creation
    .method(name, [](const Circle_3& c) {
      return jlcxx::create<Circular_arc_3>(To_spherical<SK::Circle_3>()(c));
    })
    .method(name, [](const Circle_3& c, const Point_3& pt) {
      To_spherical<Circular_arc_point_3> p2s;
      return jlcxx::create<Circular_arc_3>(To_spherical<SK::Circle_3>()(c),
                                           p2s(pt));
    })
    .method(name, [](const Circle_3& c, const Point_3& p, const Point_3& q) {
      To_spherical<Circular_arc_point_3> p2s;
      return jlcxx::create<Circular_arc_3>(To_spherical<SK::Circle_3>()(c),
                                           p2s(p), p2s(q));
    })
    .method(name, [](const Point_3& p, const Point_3& q, const Point_3& r) {
      To_spherical<SK::Point_3> p2s;
      return jlcxx::create<Circular_arc_3>(p2s(p), p2s(q), p2s(r));
    })
    // Access Functions
    .method("supporting_circle", [](const Circular_arc_3& ca) {
      return To_linear<SK::Circle_3>()(ca.supporting_circle());
    })
    .method("center", [](const Circular_arc_3& ca) {
      return To_linear<SK::Point_3>()(ca.center());
    })
    .METHOD(Circular_arc_3, squared_radius)
    .method("supporting_plane", [](const Circular_arc_3& ca) {
      return To_linear<SK::Plane_3>()(ca.supporting_plane());
    })
    .method("diametral_sphere", [](const Circular_arc_3& ca) {
      return To_linear<SK::Sphere_3>()(ca.diametral_sphere());
    })
    .method("source", [](const Circular_arc_3& ca) {
      return To_linear<Circular_arc_point_3>()(ca.source());
    })
    .method("target", [](const Circular_arc_3& ca) {
      return To_linear<Circular_arc_point_3>()(ca.target());
    })
    OVERRIDE_BASE(kernel, circular_arc_3)
    .BINARY_OP_SELF(const Circular_arc_3&, ==)
    UNSET_OVERRIDE(kernel, circular_arc_3)
    // Representation
    .method("repr", [](const Circular_arc_3& ca) {
      To_linear<Circular_arc_point_3> p2l;

      auto c = To_linear<SK::Circle_3>()(ca.supporting_circle());
      auto s = p2l(ca.source());
      auto t = p2l(ca.target());

      std::ostringstream oss("");
      CGAL::set_pretty_mode(oss);
      oss << c << ", " << s << ", " << t;

      return oss.str();
    })
    ;
}
