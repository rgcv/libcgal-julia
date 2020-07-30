#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>

#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"
#include "utils.hpp"

namespace jlcgal {

template<typename P1, typename P2>
bool
eqpoly(const P1& p1, const P2& p2) { return p1 == p2; }

void wrap_polygon_2(jlcxx::Module& cgal) {
  typedef CGAL::Polygon_2<Kernel> Poly_2;
  const std::string poly_2_name = "Polygon2";

  auto poly_2 = cgal.add_type<Poly_2>(poly_2_name)
    // Creation
    .constructor<const Poly_2&>()
    .method(poly_2_name, [](jlcxx::ArrayRef<Point_2> ps) {
      return jlcxx::create<Poly_2>(ps.begin(), ps.end());
    })
    .method("transform", [](const Aff_transformation_2& t, const Poly_2& poly) {
      return CGAL::transform(t, poly);
    })
    // I/O
    .TO_STRING(Poly_2)
    ;
  cgal.set_override_module(jl_base_module);
  poly_2
    // Modifiers
    .method("empty!", [](Poly_2& poly) -> Poly_2& {
      poly.clear();
      return poly;
    })
    .method("push!", [](Poly_2& poly, const Point_2& p) -> Poly_2& {
      poly.push_back(p);
      return poly;
    })
    .method("reverse", [](const Poly_2& poly) {
      Poly_2 p(poly);
      p.reverse_orientation();
      return p;
    })
    .method("reverse!", [](Poly_2& poly) -> Poly_2& {
      poly.reverse_orientation();
      return poly;
    })
    ;
  cgal.unset_override_module();
  poly_2
    // Access Functions
    .method("vertices", [](const Poly_2& poly) {
      return collect(poly.vertices_begin(), poly.vertices_end());
    })
    .method("edges", [](const Poly_2& poly) {
      return collect(poly.edges_begin(), poly.edges_end());
    })
    // Predicates
    .method("is_simple",     &Poly_2::is_simple)
    .method("is_convex",     &Poly_2::is_convex)
    .method("orientation",   &Poly_2::orientation)
    .method("oriented_side", &Poly_2::oriented_side)
    .method("bounded_side",  &Poly_2::bounded_side)
    .method("bbox",          &Poly_2::bbox)
    .method("area",          &Poly_2::area)
    .method("left_vertex", [](const Poly_2& poly) {
      return *poly.left_vertex();
    })
    .method("right_vertex", [](const Poly_2& poly) {
      return *poly.right_vertex();
    })
    .method("top_vertex", [](const Poly_2& poly) {
      return *poly.top_vertex();
    })
    .method("bottom_vertex", [](const Poly_2& poly) {
      return *poly.bottom_vertex();
    })
    // Convenience Orientation Functions
    .method("is_counterclockwise_oriented", &Poly_2::is_counterclockwise_oriented)
    .method("is_clockwise_oriented",        &Poly_2::is_clockwise_oriented)
    .method("is_collinear_oriented",        &Poly_2::is_collinear_oriented)
    .method("has_on_positive_side",         &Poly_2::has_on_positive_side)
    .method("has_on_negative_side",         &Poly_2::has_on_negative_side)
    .method("has_on_boundary",              &Poly_2::has_on_boundary)
    .method("has_on_bounded_side",          &Poly_2::has_on_bounded_side)
    .method("has_on_unbounded_side",        &Poly_2::has_on_unbounded_side)
    ;
  cgal.set_override_module(jl_base_module);
  poly_2
    // Miscellaneous
    .method("isempty", &Poly_2::is_empty)
    .method("length",  &Poly_2::size)
    .method("resize!", [](Poly_2& poly, const jlcxx::cxxint_t i) -> Poly_2& {
      poly.resize(i);
      return poly;
    })
    ;
  cgal.unset_override_module();

  typedef CGAL::Polygon_with_holes_2<Kernel> Pwh_2;
  const std::string pwh_2_name = "PolygonWithHoles2";

  auto pwh_2 = cgal.add_type<Pwh_2>(pwh_2_name)
    // Public Member Functions
    .constructor<const Poly_2&>()
    .method(pwh_2_name, [](const Poly_2& outer, jlcxx::ArrayRef<Poly_2> ps) {
      return Pwh_2(outer, ps.begin(), ps.end());
    })
    .method("bbox", &Pwh_2::bbox)
    // Predicates
    .method("has_holes",    &Pwh_2::has_holes)
    .method("is_unbounded", &Pwh_2::is_unbounded)
    .method("is_plane",     &Pwh_2::is_plane)
    // Access Functions
    .method("number_of_holes", &Pwh_2::number_of_holes)
    .method("outer_boundary", [](const Pwh_2& poly) -> const Poly_2& {
      return poly.outer_boundary();
    })
    .method("holes", [](const Pwh_2& poly) {
      return collect(poly.holes_begin(), poly.holes_end());
    })
    // Modifiers
    .method("add_hole", &Pwh_2::add_hole)
    .method("erase_hole", [](Pwh_2& poly, const Poly_2& hole) {
      poly.erase_hole(std::find(poly.holes_begin(), poly.holes_end(), hole));
    })
    ;
  cgal.set_override_module(jl_base_module);
  pwh_2
    .method("empty!", [](Pwh_2& poly) -> Pwh_2& {
      poly.clear();
      return poly;
    })
    ;
  cgal.unset_override_module();
  pwh_2
    // Related Functions
    .TO_STRING(Pwh_2)
    ;

  cgal.set_override_module(jl_base_module);
  cgal.method("==", &eqpoly<Poly_2, Poly_2>);
  cgal.method("==", &eqpoly<Poly_2, Pwh_2>);
  cgal.method("==", &eqpoly<Pwh_2, Poly_2>);
  cgal.method("==", &eqpoly<Pwh_2, Pwh_2>);
  cgal.unset_override_module();
}

} // jlcgal
