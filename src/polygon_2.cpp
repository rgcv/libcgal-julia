#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"
#include "utils.hpp"

typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel> Polygon_with_holes_2;

void wrap_polygon_2(jlcxx::Module& cgal) {
  const std::string poly_2_name = "Polygon2";
  auto poly_2 = cgal.add_type<Polygon_2>(poly_2_name)
    // Creation
    .CTOR(const Polygon_2&)
    .method(poly_2_name, [](jlcxx::ArrayRef<Point_2> ps) {
      return jlcxx::create<Polygon_2>(ps.begin(), ps.end());
    })
    // Global Operations
    OVERRIDE_BASE(cgal, poly_2)
    .BINARY_OP_SELF(Polygon_2, ==)
    UNSET_OVERRIDE(cgal, poly_2)
    .method("transform", [](const Aff_transformation_2& t,
                            const Polygon_2& poly) {
      return CGAL::transform(t, poly);
    })
    // I/O
    .REPR(Polygon_2)
    // Modifiers
    OVERRIDE_BASE(cgal, poly_2)
    .method("empty!", [](Polygon_2& poly) {
      poly.clear();
      return poly;
    })
    .method("push!", [](Polygon_2& poly, const Point_2& p) {
      poly.push_back(p);
      return poly;
    })
    .method("reverse", [](const Polygon_2& poly) {
      Polygon_2 p(poly);
      p.reverse_orientation();
      return p;
    })
    .method("reverse!", [](Polygon_2& poly) {
      poly.reverse_orientation();
      return poly;
    })
    UNSET_OVERRIDE(cgal, poly_2)
    // Access Functions
    .method("vertices", [](const Polygon_2& poly) {
      return collect(poly.vertices_begin(), poly.vertices_end());
    })
    .method("edges", [](const Polygon_2& poly) {
      return collect(poly.edges_begin(), poly.edges_end());
    })
    // Predicates
    .METHOD(Polygon_2, is_simple)
    .METHOD(Polygon_2, is_convex)
    .METHOD(Polygon_2, orientation)
    .METHOD(Polygon_2, oriented_side)
    .METHOD(Polygon_2, bounded_side)
    .METHOD(Polygon_2, bbox)
    .METHOD(Polygon_2, area)
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
    .METHOD(Polygon_2, is_counterclockwise_oriented)
    .METHOD(Polygon_2, is_clockwise_oriented)
    .METHOD(Polygon_2, is_collinear_oriented)
    .METHOD(Polygon_2, has_on_positive_side)
    .METHOD(Polygon_2, has_on_negative_side)
    .METHOD(Polygon_2, has_on_boundary)
    .METHOD(Polygon_2, has_on_bounded_side)
    .METHOD(Polygon_2, has_on_unbounded_side)
    // Miscellaneous
    OVERRIDE_BASE(cgal, poly_2)
    .method("isempty", &Polygon_2::is_empty)
    .method("length", &Polygon_2::size)
    .method("resize!", [](Polygon_2& poly, const jlcxx::cxxint_t i) {
      poly.resize(i);
      return poly;
    })
    UNSET_OVERRIDE(cgal, poly_2)
    ;

  const std::string poly_2_w_holes_name = "PolygonWithHoles2";
  auto poly_2_w_holes = cgal.add_type<Polygon_with_holes_2>(poly_2_w_holes_name)
    // Public Member Functions
    .CTOR(const Polygon_2&)
    .method(poly_2_w_holes_name, [](const Polygon_2& outer,
                                    jlcxx::ArrayRef<Polygon_2> ps) {
      return Polygon_with_holes_2(outer, ps.begin(), ps.end());
    })
    .METHOD(Polygon_with_holes_2, bbox)
    // Predicates
    .METHOD(Polygon_with_holes_2, is_unbounded)
    // Access Functions
    .UNAMBIG_METHOD(const Polygon_2&, Polygon_with_holes_2, outer_boundary)
    .method("holes", [](const Polygon_with_holes_2& poly) {
      return collect(poly.holes_begin(), poly.holes_end());
    })
    // Related Functions
    .REPR(Polygon_with_holes_2)
    ;
}
