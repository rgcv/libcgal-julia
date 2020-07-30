#include <sstream>
#include <string>

#include <CGAL/IO/io.h>

#include <jlcxx/module.hpp>

#include <julia.h>

#include "kernel.hpp"
#include "kernel_conversion.hpp"

namespace jlcgal {

void wrap_circular_arc_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Circular_arc_2>& circular_arc_2) {
  const std::string ca_name = jlcxx::julia_type_name(circular_arc_2.dt());

  kernel.set_override_module(jl_base_module);
  circular_arc_2
    // Related Functions
    .method("==", [](const Circular_arc_2& ca1, const Circular_arc_2& ca2) {
      return ca1 == ca2;
    })
    ;
  kernel.unset_override_module();
  circular_arc_2
    // Creation
    .method(ca_name, [](const Circle_2& c) {
      return jlcxx::create<Circular_arc_2>(To_circular<CK::Circle_2>()(c));
    })
    .method(ca_name, [](const Circle_2& c, const Point_2& p, const Point_2& q) {
      To_circular<CK::Circular_arc_point_2> p2c;
      return jlcxx::create<Circular_arc_2>(To_circular<CK::Circle_2>()(c),
                                           p2c(p), p2c(q));
    })
    .method(ca_name, [](const Point_2& p, const Point_2& q, const Point_2& r) {
      To_circular<CK::Point_2> p2c;
      return jlcxx::create<Circular_arc_2>(p2c(p), p2c(q), p2c(r));
    })
    // Access Functions
    .method("supporting_circle", [](const Circular_arc_2& ca) {
      return To_linear<CK::Circle_2>()(ca.supporting_circle());
    })
    .method("center", [](const Circular_arc_2& ca) {
      return To_linear<CK::Point_2>()(ca.center());
    })
    .method("squared_radius", &Circular_arc_2::squared_radius)
    .method("source", [](const Circular_arc_2& ca) {
      return To_linear<CK::Circular_arc_point_2>()(ca.source());
    })
    .method("target", [](const Circular_arc_2& ca) {
      return To_linear<CK::Circular_arc_point_2>()(ca.target());
    })
    .method("left", [](const Circular_arc_2& ca) {
      return To_linear<CK::Circular_arc_point_2>()(ca.left());
    })
    .method("right", [](const Circular_arc_2& ca) {
      return To_linear<CK::Circular_arc_point_2>()(ca.right());
    })
    .method("bbox", &Circular_arc_2::bbox)
    // Query Functions
    .method("is_x_monotone", &Circular_arc_2::is_x_monotone)
    .method("is_y_monotone", &Circular_arc_2::is_y_monotone)
    // Representation
    .method("_tostring", [](const Circular_arc_2& ca) {
      To_linear<CK::Circular_arc_point_2> p2l;

      auto c = To_linear<CK::Circle_2>()(ca.supporting_circle());
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
