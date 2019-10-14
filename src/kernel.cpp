#include <julia/julia.h>
#include <jlcxx/jlcxx.hpp>
#include <jlcxx/type_conversion.hpp>

#include <type_traits>

#include "io.hpp"
#include "kernel.hpp"

template<typename T>
double to_double(const T& t) { return CGAL::to_double(t); }

#define CGAL_CONST(name) cgal.set_const(#name, CGAL::name)

#define UNARY_OP(op, T) method(#op, [](const T& t) { return op t; })
#define BINARY_OP(T1, op, T2) \
  method(#op, [](const T1& t1, const T2& t2) { return t1 op t2; })
#define BINARY_OP_SELF(op, T) BINARY_OP(T, op, T)

namespace jlcxx {
  template<> struct IsBits<Angle>             : std::true_type {};
  template<> struct IsBits<Bounded_side>      : std::true_type {};
  // Covers Comparison_result, Orientation, and Oriented_side
  template<> struct IsBits<Sign>              : std::true_type {};
}

void wrap_kernel(jlcxx::Module& cgal) {
  /// TYPES ====================================================================

  jl_value_t* jl_real = jlcxx::julia_type("Real", "Base");
  auto field_type = cgal.add_type<FT>("FieldType", jl_real);

  auto aff_transformation_2 = cgal.add_type<Aff_transformation_2>("AffTransformation2");
  auto bbox_2 = cgal.add_type<Bbox_2>("BBox2");
  auto circle_2 = cgal.add_type<Circle_2>("Circle2");
  auto direction_2 = cgal.add_type<Direction_2>("Direction2");
  auto iso_rectangle_2 = cgal.add_type<Iso_rectangle_2>("IsoRectangle2");
  auto line_2 = cgal.add_type<Line_2>("Line2");
  auto point_2 = cgal.add_type<Point_2>("Point2");
  auto ray_2 = cgal.add_type<Ray_2>("Ray2");
  auto segment_2 = cgal.add_type<Segment_2>("Segment2");
  auto triangle_2 = cgal.add_type<Triangle_2>("Triangle2");
  auto vector_2 = cgal.add_type<Vector_2>("Vector2");
  auto weighted_point_2 = cgal.add_type<Weighted_point_2>("WeightedPoint2");

  /// CONSTANTS ================================================================

  jl_value_t *jl_cpp_enum = jlcxx::julia_type("CppEnum");
  // Can't set consts, they get erased post pre-compilation.
  // Therefore, their constant counterparts are defined on the julia side.
  cgal.add_type<Identity_transformation>("IdentityTransformation");
  cgal.add_type<Null_vector>("NullVector");
  cgal.add_type<Origin>("Origin");
  cgal.add_type<Rotation>("Rotation");
  cgal.add_type<Scaling>("Scaling");
  cgal.add_type<Translation>("Translation");

  // Angle: Angle classification/type
  cgal.add_bits<Angle>("Angle", jl_cpp_enum);
  CGAL_CONST(OBTUSE); CGAL_CONST(RIGHT); CGAL_CONST(ACUTE);

  // Bounded_side: Placement relative to boundary
  cgal.add_bits<Bounded_side>("BoundedSide");
  CGAL_CONST(ON_UNBOUNDED_SIDE); CGAL_CONST(ON_BOUNDARY); CGAL_CONST(ON_BOUNDED_SIDE);

  // Sign: Object sign
  cgal.add_bits<Sign>("Sign", jl_cpp_enum);
  CGAL_CONST(NEGATIVE); CGAL_CONST(ZERO); CGAL_CONST(POSITIVE);

  // Orientation: Object orientation (Aliased to Sign in Julia)
  CGAL_CONST(LEFT_TURN); CGAL_CONST(RIGHT_TURN);
  CGAL_CONST(CLOCKWISE); CGAL_CONST(COUNTERCLOCKWISE);
  CGAL_CONST(COLLINEAR); CGAL_CONST(COPLANAR); CGAL_CONST(DEGENERATE);

  // Oriented_side: Side orientation (Aliased to Sign in Julia)
  CGAL_CONST(ON_NEGATIVE_SIDE); CGAL_CONST(ON_ORIENTED_BOUNDARY); CGAL_CONST(ON_POSITIVE_SIDE);

  // Comparison_result: Result relative size (Aliased to Sign in Julia)
  CGAL_CONST(SMALLER); CGAL_CONST(EQUAL); CGAL_CONST(LARGER);

  /// TYPES (cont.) ============================================================

  field_type
    // Creation
    .constructor<double>()
    // RealEmbeddable Operations
    .BINARY_OP_SELF(==, FT)
    .BINARY_OP_SELF(<,  FT)
    .BINARY_OP_SELF(<=, FT)
    .BINARY_OP_SELF(>,  FT)
    .BINARY_OP_SELF(>=, FT)
    // Field Operations
    .BINARY_OP_SELF(/, FT)
    // IntegralDomainWithoutDivision Operations
    .BINARY_OP_SELF(+, FT)
    .BINARY_OP_SELF(-, FT)
    .BINARY_OP_SELF(*, FT)
    .UNARY_OP(+, FT)
    .UNARY_OP(-, FT)
    // Converter
    .method("to_double", &to_double<FT>)
    // Representation
    .method("repr", &repr<FT>)
    ;

  aff_transformation_2
      // Creation
      .constructor<Identity_transformation>()
      .constructor<Translation, Vector_2>()
      .constructor<Rotation, Direction_2, RT>()
      .constructor<Rotation, Direction_2, RT, RT>()
      .constructor<Rotation, RT, RT>()
      .constructor<Rotation, RT, RT, RT>()
      .constructor<Scaling, RT>()
      .constructor<Scaling, RT, RT>()
      .constructor<RT, RT, RT, RT, RT, RT>()
      .constructor<RT, RT, RT, RT, RT, RT, RT>()
      .constructor<RT, RT, RT, RT>()
      .constructor<RT, RT, RT, RT, RT>()
      // Operations
      // NOTE: Invocation operator should be defined on julia's side
      .method("transform", [](const Aff_transformation_2& t, const Point_2& p    ) { return t.transform(p); })
      .method("transform", [](const Aff_transformation_2& t, const Vector_2& v   ) { return t.transform(v); })
      .method("transform", [](const Aff_transformation_2& t, const Direction_2& d) { return t.transform(d); })
      .method("transform", [](const Aff_transformation_2& t, const Line_2& l     ) { return t.transform(l); })
      .method(static_cast<Point_2     (Aff_transformation_2::*)(const Point_2&    ) const>(&Aff_transformation_2::operator()))
      .method(static_cast<Vector_2    (Aff_transformation_2::*)(const Vector_2&   ) const>(&Aff_transformation_2::operator()))
      .method(static_cast<Direction_2 (Aff_transformation_2::*)(const Direction_2&) const>(&Aff_transformation_2::operator()))
      .method(static_cast<Line_2      (Aff_transformation_2::*)(const Line_2&     ) const>(&Aff_transformation_2::operator()))
      // Miscellaneous
      .BINARY_OP_SELF(==, Aff_transformation_2)
      .BINARY_OP_SELF(*,  Aff_transformation_2)
      .method("inverse", &Aff_transformation_2::inverse)
      .method("is_even", &Aff_transformation_2::is_even)
      .method("is_odd",  &Aff_transformation_2::is_odd )
      // Matrix Entry Access
      .method("cartesian",   &Aff_transformation_2::cartesian  )
      .method("m",           &Aff_transformation_2::m          )
      .method("homogeneous", &Aff_transformation_2::homogeneous)
      .method("hm",          &Aff_transformation_2::hm         )
      // Representation
      .method("repr", &repr<Aff_transformation_2>)
      ;

  bbox_2
    // Creation
    .constructor<double, double, double, double>()
    // Operations
    .BINARY_OP_SELF(==, Bbox_2)
    .BINARY_OP_SELF(+,  Bbox_2)
    .method("dimension", &Bbox_2::dimension)
    .method("xmin",      &Bbox_2::xmin     )
    .method("ymin",      &Bbox_2::ymin     )
    .method("xmax",      &Bbox_2::xmax     )
    .method("ymax",      &Bbox_2::ymax     )
    .method("min",       &Bbox_2::min      )
    .method("max",       &Bbox_2::max      )
    .method("dilate",    &Bbox_2::dilate   )
    // Representation
    .method("repr", &repr<Bbox_2>)
    ;

  circle_2
    // Creation
    .constructor<Point_2, FT>()
    .constructor<Point_2, FT, Orientation>()
    .constructor<Point_2, Point_2, Point_2>()
    .constructor<Point_2, Point_2>()
    .constructor<Point_2, Point_2, Orientation>()
    .constructor<Point_2>()
    .constructor<Point_2, Orientation>()
    // Access Functions
    .method("center",         &Circle_2::center        )
    .method("squared_radius", &Circle_2::squared_radius)
    .method("orientation",    &Circle_2::orientation   )
    .BINARY_OP_SELF(==, Circle_2)
    // Predicates
    .method("is_degenerate",         &Circle_2::is_degenerate        )
    .method("oriented_side",         &Circle_2::oriented_side        )
    .method("bounded_side",          &Circle_2::bounded_side         )
    .method("has_on_positive_side",  &Circle_2::has_on_positive_side )
    .method("has_on_negative_side",  &Circle_2::has_on_negative_side )
    .method("has_on_boundary",       &Circle_2::has_on_boundary      )
    .method("has_on_bounded_side",   &Circle_2::has_on_bounded_side  )
    .method("has_on_unbounded_side", &Circle_2::has_on_unbounded_side)
    // Miscellaneous
    .method("opposite",             &Circle_2::opposite            )
    .method("orthogonal_transform", &Circle_2::orthogonal_transform)
    .method("bbox",                 &Circle_2::bbox                )
    // Representation
    .method("repr", &repr<Circle_2>)
    ;

  direction_2
    // Creation
    .constructor<Vector_2>()
    .constructor<Line_2>()
    .constructor<Ray_2>()
    .constructor<Segment_2>()
    .constructor<RT, RT>()
    // Operations
    .method("delta", &Direction_2::delta   )
    .method("dx",    &Direction_2::dx      )
    .method("dy",    &Direction_2::dy      )
    .BINARY_OP_SELF(==, Direction_2)
    .BINARY_OP_SELF(<,  Direction_2)
    .BINARY_OP_SELF(>,  Direction_2)
    .BINARY_OP_SELF(<=, Direction_2)
    .BINARY_OP_SELF(>=, Direction_2)
    .method("counterclockwise_in_between", &Direction_2::counterclockwise_in_between)
    .UNARY_OP(-, Direction_2)
    // Miscellaneous
    .method("vector",    &Direction_2::vector   )
    .method("transform", &Direction_2::transform)
    // Representation
    .method("repr", &repr<Direction_2>)
    ;

  iso_rectangle_2
    // Creation
    .constructor<Point_2, Point_2>()
    .constructor<Point_2, Point_2, int>()
    .constructor<Point_2, Point_2, Point_2, Point_2>()
    .constructor<RT, RT, RT, RT>()
    .constructor<Bbox_2>()
    // Operations
    .BINARY_OP_SELF(==, Iso_rectangle_2)
    .method("vertex",    &Iso_rectangle_2::vertex   )
    .method("min",       &Iso_rectangle_2::min      )
    .method("max",       &Iso_rectangle_2::max      )
    .method("xmin",      &Iso_rectangle_2::xmin     )
    .method("ymin",      &Iso_rectangle_2::ymin     )
    .method("xmax",      &Iso_rectangle_2::xmax     )
    .method("ymax",      &Iso_rectangle_2::ymax     )
    .method("min_coord", &Iso_rectangle_2::min_coord)
    .method("max_coord", &Iso_rectangle_2::max_coord)
    // Predicates
    .method("is_degenerate",         &Iso_rectangle_2::is_degenerate        )
    .method("bounded_side",          &Iso_rectangle_2::bounded_side         )
    .method("has_on_boundary",       &Iso_rectangle_2::has_on_boundary      )
    .method("has_on_bounded_side",   &Iso_rectangle_2::has_on_bounded_side  )
    .method("has_on_unbounded_side", &Iso_rectangle_2::has_on_unbounded_side)
    // Miscellaneous
    .method("area",      &Iso_rectangle_2::area     )
    .method("bbox",      &Iso_rectangle_2::bbox     )
    .method("transform", &Iso_rectangle_2::transform)
    ;

  line_2
    // Creation
    .constructor<RT, RT, RT>()
    .constructor<Point_2, Point_2>()
    .constructor<Point_2, Direction_2>()
    .constructor<Point_2, Vector_2>()
    .constructor<Segment_2>()
    .constructor<Ray_2>()
    // Operators
    .BINARY_OP_SELF(==, Line_2)
    .method("a",          &Line_2::a         )
    .method("b",          &Line_2::b         )
    .method("c",          &Line_2::c         )
    .method("point",      [](const Line_2& l, int i) { return l.point(i); })
    .method("projection", &Line_2::projection)
    .method("x_at_y",     &Line_2::x_at_y    )
    .method("y_at_x",     &Line_2::y_at_x    )
    // Predicates
    .method("is_degenerate", &Line_2::is_degenerate)
    .method("is_horizontal", &Line_2::is_horizontal)
    .method("is_vertical",   &Line_2::is_vertical  )
    .method("oriented_side", &Line_2::oriented_side)
    // Convenience boolean functions
    .method("has_on",               &Line_2::has_on              )
    .method("has_on_positive_side", &Line_2::has_on_positive_side)
    .method("has_on_negative_side", &Line_2::has_on_negative_side)
    // Miscellaneous
    .method("to_vector",      &Line_2::to_vector    )
    .method("direction",      &Line_2::direction    )
    .method("opposite",       &Line_2::opposite     )
    .method("perpendicular",  &Line_2::perpendicular)
    .method("transform",      &Line_2::transform    )
    // Representation
    .method("repr", &repr<Line_2>)
    ;

  point_2
    // Related Functions
    .BINARY_OP_SELF(<,  Point_2)
    .BINARY_OP_SELF(>,  Point_2)
    .BINARY_OP_SELF(<=, Point_2)
    .BINARY_OP_SELF(>=, Point_2)
    .BINARY_OP_SELF(-,  Point_2)
    .BINARY_OP(Point_2, ==, Origin  )
    .BINARY_OP(Point_2, +,  Vector_2)
    .BINARY_OP(Point_2, -,  Vector_2)
    // Creation
    .constructor<Origin>()
    .constructor<int, int>()
    .constructor<double, double>()
    .constructor<RT, RT, RT>()
    .constructor<FT, FT>() // in a Cartesian kernel, covers (RT, RT) ctor
    .constructor<Weighted_point_2>()
    // Operations
    .BINARY_OP_SELF(==, Point_2)
    // Coordinate Access
    .method("hx", &Point_2::hx)
    .method("hy", &Point_2::hy)
    .method("hw", &Point_2::hw)
    .method("x",  &Point_2::x )
    .method("y",  &Point_2::y )
    // Convenience Operations
    .method("homogeneous", &Point_2::homogeneous)
    .method("cartesian",   &Point_2::cartesian  )
    // TODO: missing cartesian iteratior methods
    .method("dimension",   &Point_2::dimension  )
    .method("bbox",        &Point_2::bbox       )
    .method("transform",   &Point_2::transform  )
    // Representation
    .method("repr", &repr<Point_2>)
    ;

  ray_2
    // Creation
    .constructor<Point_2, Point_2>()
    .constructor<Point_2, Direction_2>()
    .constructor<Point_2, Vector_2>()
    .constructor<Point_2, Line_2>()
    // Operations
    .BINARY_OP_SELF(==, Ray_2)
    .method("source",          &Ray_2::source         )
    .method("point",           &Ray_2::point          )
    .method("direction",       &Ray_2::direction      )
    .method("to_vector",       &Ray_2::to_vector      )
    .method("supporting_line", &Ray_2::supporting_line)
    .method("opposite",        &Ray_2::opposite       )
    // Predicates
    .method("is_degenerate",    &Ray_2::is_degenerate   )
    .method("is_horizontal",    &Ray_2::is_horizontal   )
    .method("is_vertical",      &Ray_2::is_vertical     )
    .method("has_on",           &Ray_2::has_on          )
    .method("collinear_has_on", &Ray_2::collinear_has_on)
    // Miscellaneous
    .method("transform", &Ray_2::transform)
    // Representation
    .method("repr", &repr<Ray_2>)
    ;

  segment_2
    // Creation
    .constructor<Point_2, Point_2>()
    // Operations
    .BINARY_OP_SELF(==, Segment_2)
    .method("source",          &Segment_2::source         )
    .method("target",          &Segment_2::target         )
    .method("min",             &Segment_2::min            )
    .method("max",             &Segment_2::max            )
    .method("vertex",          &Segment_2::vertex         )
    .method("point",           &Segment_2::point          )
    .method("squared_length",  &Segment_2::squared_length )
    .method("direction",       &Segment_2::direction      )
    .method("to_vector",       &Segment_2::to_vector      )
    .method("opposite",        &Segment_2::opposite       )
    .method("supporting_line", &Segment_2::supporting_line)
    // Predicates
    .method("is_degenerate",    &Segment_2::is_degenerate   )
    .method("is_horizontal",    &Segment_2::is_horizontal   )
    .method("is_vertical",      &Segment_2::is_vertical     )
    .method("has_on",           &Segment_2::has_on          )
    .method("collinear_has_on", &Segment_2::collinear_has_on)
    // Miscellaneous
    .method("bbox",      &Segment_2::bbox     )
    .method("transform", &Segment_2::transform)
    // Representation
    .method("repr", &repr<Segment_2>)
    ;

  triangle_2
    // Creation
    .constructor<Point_2, Point_2, Point_2>()
    // Operations
    .BINARY_OP_SELF(==, Triangle_2)
    .method("vertex", &Triangle_2::vertex)
    // Predicates
    .method("is_degenerate", &Triangle_2::is_degenerate)
    .method("orientation",   &Triangle_2::orientation  )
    .method("oriented_side", &Triangle_2::oriented_side)
    .method("bounded_side",  &Triangle_2::bounded_side )
    .method("has_on_positive_side",  &Triangle_2::has_on_positive_side )
    .method("has_on_negative_side",  &Triangle_2::has_on_negative_side )
    .method("has_on_boundary",       &Triangle_2::has_on_boundary      )
    .method("has_on_bounded_side",   &Triangle_2::has_on_bounded_side  )
    .method("has_on_unbounded_side", &Triangle_2::has_on_unbounded_side)
    // Miscellaneous
    .method("opposite",  &Triangle_2::opposite )
    .method("area",      &Triangle_2::area     )
    .method("bbox",      &Triangle_2::bbox     )
    .method("transform", &Triangle_2::transform)
    ;

  vector_2
    // Public Member Functions
    .method("squared_length", &Vector_2::squared_length)
    .BINARY_OP(Vector_2, *, FT) // in Cartesian kernel, FT = RT
    .BINARY_OP(FT, *, Vector_2) // ^ idem
    .BINARY_OP(Origin, +, Vector_2)
    // Creation
    .constructor<Point_2, Point_2>()
    .constructor<Segment_2>()
    .constructor<Ray_2>()
    .constructor<Line_2>()
    .constructor<Null_vector>()
    .constructor<int, int>()
    .constructor<double, double>()
    .constructor<RT, RT, RT>()
    .constructor<FT, FT>()
    // Coordinate Access
    .method("hx", &Vector_2::hx)
    .method("hy", &Vector_2::hy)
    .method("hw", &Vector_2::hw)
    .method("x",  &Vector_2::x )
    .method("y",  &Vector_2::y )
    // Convenience Operators
    .method("homogeneous",    &Vector_2::homogeneous  )
    .method("cartesian",      &Vector_2::cartesian    )
    // TODO: missing cartesian iteratior methods
    .method("dimension",      &Vector_2::dimension    )
    .method("direction",      &Vector_2::direction    )
    .method("transform",      &Vector_2::transform    )
    .method("perpendicular",  &Vector_2::perpendicular)
    // Operators
    .BINARY_OP_SELF(==, Vector_2)
    .BINARY_OP_SELF(+,  Vector_2)
    .BINARY_OP_SELF(-,  Vector_2)
    .UNARY_OP(-, Vector_2)
    .BINARY_OP_SELF(*,  Vector_2)
    .BINARY_OP(Vector_2, /,  RT)
    .BINARY_OP(Vector_2, *,  RT)
    //.BINARY_OP(Vector_2, *,  RT      )
    // Representation
    .method("repr", &repr<Vector_2>)
    ;

  weighted_point_2
    // Creation
    .constructor<Origin>()
    .constructor<Point_2>()
    .constructor<Point_2, FT>()
    .constructor<FT, FT>()
    // Bare point and weight accessor
    .method("point",  &Weighted_point_2::point )
    .method("weight", &Weighted_point_2::weight)
    // Operations (delegated to underlying Point_2)
    .BINARY_OP_SELF(==, Weighted_point_2)
    .BINARY_OP_SELF(<,  Weighted_point_2)
    // Coordinate Access
    .method("hx", &Weighted_point_2::hx)
    .method("hy", &Weighted_point_2::hy)
    .method("hw", &Weighted_point_2::hw)
    .method("x",  &Weighted_point_2::x )
    .method("y",  &Weighted_point_2::y )
    // Convenience Operations
    .method("homogeneous", &Weighted_point_2::homogeneous )
    .method("cartesian",   &Weighted_point_2::cartesian   )
    .method("dimension",   &Weighted_point_2::dimension   )
    .method("bbox",        &Weighted_point_2::bbox        )
    // Compiler doesn't like an affine transformation object with a
    // transform method with 2 arguments.. despite it being used in
    // Weighted_point_2.h.. Mind boggling
    //.method("transform",   &Weighted_point_2::transform   )
    .method("transform",   [](const Weighted_point_2 &wp, const Aff_transformation_2 &t) {
        return Weighted_point_2(t.transform(wp.point()), wp.weight());
    })
    // Representation
    .method("repr",        &repr<Weighted_point_2>)
    ;

}
