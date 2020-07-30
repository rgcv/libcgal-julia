#include <sstream>
#include <string>

#include <CGAL/IO/io.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "kernel_conversion.hpp"

namespace jlcgal{

void wrap_circular_arc_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Circular_arc_3>& circular_arc_3) {
  const std::string ca_name = jlcxx::julia_type_name(circular_arc_3.dt());
  kernel.set_override_module(jl_base_module);
  circular_arc_3
    // Related Functions
    .method("==", [](const Circular_arc_3& ca1, const Circular_arc_3& ca2) {
      return ca1 == ca2;
    })
    ;
  kernel.unset_override_module();
  circular_arc_3
    // Creation
    .method(ca_name, [](const Circle_3& c) {
      return jlcxx::create<Circular_arc_3>(To_spherical<SK::Circle_3>()(c));
    })
    .method(ca_name, [](const Circle_3& c, const Point_3& pt) {
      To_spherical<SK::Circular_arc_point_3> p2s;
      return jlcxx::create<Circular_arc_3>(To_spherical<SK::Circle_3>()(c),
                                           p2s(pt));
    })
    .method(ca_name, [](const Circle_3& c, const Point_3& p, const Point_3& q) {
      To_spherical<SK::Circular_arc_point_3> p2s;
      return jlcxx::create<Circular_arc_3>(To_spherical<SK::Circle_3>()(c),
                                           p2s(p), p2s(q));
    })
    .method(ca_name, [](const Point_3& p, const Point_3& q, const Point_3& r) {
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
    .method("squared_radius", &Circular_arc_3::squared_radius)
    .method("supporting_plane", [](const Circular_arc_3& ca) {
      return To_linear<SK::Plane_3>()(ca.supporting_plane());
    })
    .method("diametral_sphere", [](const Circular_arc_3& ca) {
      return To_linear<SK::Sphere_3>()(ca.diametral_sphere());
    })
    .method("source", [](const Circular_arc_3& ca) {
      return To_linear<SK::Circular_arc_point_3>()(ca.source());
    })
    .method("target", [](const Circular_arc_3& ca) {
      return To_linear<SK::Circular_arc_point_3>()(ca.target());
    })
    // Representation
    .method("_tostring", [](const Circular_arc_3& ca) {
      To_linear<SK::Circular_arc_point_3> p2l;

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

} // jlcgal
