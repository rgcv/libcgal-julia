#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "polygon_2.hpp"
#include "utils.hpp"

namespace jlcgal {

template<typename P1, typename P2>
bool
eqpoly(const P1& p1, const P2& p2) { return p1 == p2; }

void wrap_polygon_2(jlcxx::Module& cgal) {
  const std::string poly_2_name = "Polygon2";

  auto poly_2 = cgal.add_type<Polygon_2>(poly_2_name)
    // Creation
    .constructor<const Polygon_2&>()
    .method(poly_2_name, [](jlcxx::ArrayRef<Point_2> ps) {
      return jlcxx::create<Polygon_2>(ps.begin(), ps.end());
    })
    .method("transform", [](const Aff_transformation_2& t,
                            const Polygon_2& poly) {
      return CGAL::transform(t, poly);
    })
    // I/O
    .TO_STRING(Polygon_2)
    ;
  cgal.set_override_module(jl_base_module);
  poly_2
    // Modifiers
    .method("empty!", [](Polygon_2& poly) -> Polygon_2& {
      poly.clear();
      return poly;
    })
    .method("push!", [](Polygon_2& poly, const Point_2& p) -> Polygon_2& {
      poly.push_back(p);
      return poly;
    })
    .method("reverse", [](const Polygon_2& poly) {
      Polygon_2 p(poly);
      p.reverse_orientation();
      return p;
    })
    .method("reverse!", [](Polygon_2& poly) -> Polygon_2& {
      poly.reverse_orientation();
      return poly;
    })
    ;
  cgal.unset_override_module();
  poly_2
    // Access Functions
    .method("vertices", [](const Polygon_2& poly) {
      return collect(poly.vertices_begin(), poly.vertices_end());
    })
    .method("edges", [](const Polygon_2& poly) {
      return collect(poly.edges_begin(), poly.edges_end());
    })
    // Predicates
    .method("is_simple",     &Polygon_2::is_simple)
    .method("is_convex",     &Polygon_2::is_convex)
    .method("orientation",   &Polygon_2::orientation)
    .method("oriented_side", &Polygon_2::oriented_side)
    .method("bounded_side",  &Polygon_2::bounded_side)
    .method("bbox",          &Polygon_2::bbox)
    .method("area",          &Polygon_2::area)
    .method("left_vertex", [](const Polygon_2& poly) {
      return *poly.left_vertex();
    })
    .method("right_vertex", [](const Polygon_2& poly) {
      return *poly.right_vertex();
    })
    .method("top_vertex", [](const Polygon_2& poly) {
      return *poly.top_vertex();
    })
    .method("bottom_vertex", [](const Polygon_2& poly) {
      return *poly.bottom_vertex();
    })
    // Convenience Orientation Functions
    .method("is_counterclockwise_oriented", &Polygon_2::is_counterclockwise_oriented)
    .method("is_clockwise_oriented",        &Polygon_2::is_clockwise_oriented)
    .method("is_collinear_oriented",        &Polygon_2::is_collinear_oriented)
    .method("has_on_positive_side",         &Polygon_2::has_on_positive_side)
    .method("has_on_negative_side",         &Polygon_2::has_on_negative_side)
    .method("has_on_boundary",              &Polygon_2::has_on_boundary)
    .method("has_on_bounded_side",          &Polygon_2::has_on_bounded_side)
    .method("has_on_unbounded_side",        &Polygon_2::has_on_unbounded_side)
    ;
  cgal.set_override_module(jl_base_module);
  poly_2
    // Miscellaneous
    .method("isempty", &Polygon_2::is_empty)
    .method("length",  &Polygon_2::size)
    .method("resize!", [](Polygon_2& poly, const jlcxx::cxxint_t i) -> Polygon_2& {
      poly.resize(i);
      return poly;
    })
    ;
  cgal.unset_override_module();

  const std::string pwh_2_name = "PolygonWithHoles2";

  auto pwh_2 = cgal.add_type<Polygon_with_holes_2>(pwh_2_name)
    // Public Member Functions
    .constructor<const Polygon_2&>()
    .method(pwh_2_name, [](const Polygon_2& outer,
                           jlcxx::ArrayRef<Polygon_2> ps) {
      return Polygon_with_holes_2(outer, ps.begin(), ps.end());
    })
    .method("bbox", &Polygon_with_holes_2::bbox)
    // Predicates
    .method("has_holes",    &Polygon_with_holes_2::has_holes)
    .method("is_unbounded", &Polygon_with_holes_2::is_unbounded)
    .method("is_plane",     &Polygon_with_holes_2::is_plane)
    // Access Functions
    .method("number_of_holes", &Polygon_with_holes_2::number_of_holes)
    .method("outer_boundary", [](const Polygon_with_holes_2& poly) -> const Polygon_2& {
      return poly.outer_boundary();
    })
    .method("holes", [](const Polygon_with_holes_2& poly) {
      return collect(poly.holes_begin(), poly.holes_end());
    })
    // Modifiers
    .method("add_hole", &Polygon_with_holes_2::add_hole)
    .method("erase_hole", [](Polygon_with_holes_2& poly,
                             const Polygon_2& hole) {
      poly.erase_hole(std::find(poly.holes_begin(), poly.holes_end(), hole));
    })
    ;
  cgal.set_override_module(jl_base_module);
  pwh_2
    .method("empty!", [](Polygon_with_holes_2& poly) -> Polygon_with_holes_2& {
      poly.clear();
      return poly;
    })
    ;
  cgal.unset_override_module();
  pwh_2
    // Related Functions
    .TO_STRING(Polygon_with_holes_2)
    ;

  cgal.set_override_module(jl_base_module);
  cgal.method("==", &eqpoly<Polygon_2, Polygon_2>);
  cgal.method("==", &eqpoly<Polygon_2, Polygon_with_holes_2>);
  cgal.method("==", &eqpoly<Polygon_with_holes_2, Polygon_2>);
  cgal.method("==", &eqpoly<Polygon_with_holes_2, Polygon_with_holes_2>);
  cgal.unset_override_module();
}

} // jlcgal
