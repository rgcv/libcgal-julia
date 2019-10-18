#include <julia/julia.h>
#include <jlcxx/jlcxx.hpp>
#include <jlcxx/type_conversion.hpp>

#include <type_traits>

#include "io.hpp"
#include "kernel.hpp"

template<typename T>
double to_double(const T& t) { return CGAL::to_double(t); }

#define CGAL_CONST(name) cgal.set_const(#name, CGAL::name)

#define CAST_MEMBER_FUNC(R, T, F, M, ArgsT...) \
  static_cast<R (T::*)(ArgsT) M>(&T::F)

#define CTOR(ArgsT...) constructor<ArgsT>()

#define FUNC(name, func) method(#name, &func)
#define SIMPLE_FUNC(name) FUNC(name, name)
#define PFUNC(name, func, ArgsT...) method(#name, &func<ArgsT>)
#define SIMPLE_PFUNC(name, ArgsT...) PFUNC(name, name, ArgsT)

#define METHOD(T, name) method(#name, &T::name)
#define UNAMBIG_METHOD(R, T, F, ArgsT...) \
  method(#F, CAST_MEMBER_FUNC(R, T, F, const, ArgsT))
#define INVOKE_METHOD(R, T, ArgsT...) \
  method(CAST_MEMBER_FUNC(R, T, operator(), const, ArgsT))

#define UNARY_OP(op, T) method(#op, [](const T& t) { return op t; })
#define BINARY_OP(T1, op, T2) \
  method(#op, [](const T1& t1, const T2& t2) { return t1 op t2; })
#define BINARY_OP_SELF(T, op) BINARY_OP(T, op, T)

#define REPR(T) SIMPLE_PFUNC(repr, T)

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
    .CTOR(double)
    // RealEmbeddable Operations
    .BINARY_OP_SELF(FT, ==)
    .BINARY_OP_SELF(FT,  <)
    .BINARY_OP_SELF(FT, <=)
    .BINARY_OP_SELF(FT,  >)
    .BINARY_OP_SELF(FT, >=)
    // Field Operations
    .BINARY_OP_SELF(FT, /)
    // IntegralDomainWithoutDivision Operations
    .BINARY_OP_SELF(FT, +)
    .BINARY_OP_SELF(FT, -)
    .BINARY_OP_SELF(FT, *)
    .UNARY_OP(+, FT)
    .UNARY_OP(-, FT)
    // Converter
    .SIMPLE_PFUNC(to_double, FT)
    // Representation
    .REPR(FT)
    ;

  aff_transformation_2
      // Creation
      .CTOR(Identity_transformation)
      .CTOR(Translation, Vector_2)
      .CTOR(Rotation, Direction_2, RT)
      .CTOR(Rotation, Direction_2, RT, RT)
      .CTOR(Rotation, RT, RT)
      .CTOR(Rotation, RT, RT, RT)
      .CTOR(Scaling, RT)
      .CTOR(Scaling, RT, RT)
      .CTOR(RT, RT, RT, RT, RT, RT)
      .CTOR(RT, RT, RT, RT, RT, RT, RT)
      .CTOR(RT, RT, RT, RT)
      .CTOR(RT, RT, RT, RT, RT)
      // Operations
      // NOTE: Invocation operator should be defined on julia's side
      .UNAMBIG_METHOD(Point_2,     Aff_transformation_2, transform,  const Point_2&    )
      .UNAMBIG_METHOD(Vector_2,    Aff_transformation_2, transform,  const Vector_2&   )
      .UNAMBIG_METHOD(Direction_2, Aff_transformation_2, transform,  const Direction_2&)
      .UNAMBIG_METHOD(Line_2,      Aff_transformation_2, transform,  const Line_2&     )
      .INVOKE_METHOD(Point_2,      Aff_transformation_2, const Point_2&    )
      .INVOKE_METHOD(Vector_2,     Aff_transformation_2, const Vector_2&   )
      .INVOKE_METHOD(Direction_2,  Aff_transformation_2, const Direction_2&)
      .INVOKE_METHOD(Line_2,       Aff_transformation_2, const Line_2&     )
      // Miscellaneous
      .BINARY_OP_SELF(Aff_transformation_2, ==)
      .BINARY_OP_SELF(Aff_transformation_2,  *)
      .METHOD(Aff_transformation_2, inverse)
      .METHOD(Aff_transformation_2, is_even)
      .METHOD(Aff_transformation_2, is_odd )
      // Matrix Entry Access
      .METHOD(Aff_transformation_2, cartesian  )
      .METHOD(Aff_transformation_2, m          )
      .METHOD(Aff_transformation_2, homogeneous)
      .METHOD(Aff_transformation_2, hm         )
      // Representation
      .REPR(Aff_transformation_2)
      ;

  bbox_2
    // Creation
    .CTOR(double, double, double, double)
    // Operations
    .BINARY_OP_SELF(Bbox_2, ==)
    .BINARY_OP_SELF(Bbox_2,  +)
    .METHOD(Bbox_2, dimension)
    .METHOD(Bbox_2, xmin     )
    .METHOD(Bbox_2, ymin     )
    .METHOD(Bbox_2, xmax     )
    .METHOD(Bbox_2, ymax     )
    .METHOD(Bbox_2, min      )
    .METHOD(Bbox_2, max      )
    .METHOD(Bbox_2, dilate   )
    // Representation
    .REPR(Bbox_2)
    ;

  circle_2
    // Creation
    .CTOR(Point_2, FT)
    .CTOR(Point_2, FT, Orientation)
    .CTOR(Point_2, Point_2, Point_2)
    .CTOR(Point_2, Point_2)
    .CTOR(Point_2, Point_2, Orientation)
    .CTOR(Point_2)
    .CTOR(Point_2, Orientation)
    // Access Functions
    .METHOD(Circle_2, center        )
    .METHOD(Circle_2, squared_radius)
    .METHOD(Circle_2, orientation   )
    .BINARY_OP_SELF(Circle_2, ==)
    // Predicates
    .METHOD(Circle_2, is_degenerate        )
    .METHOD(Circle_2, oriented_side        )
    .METHOD(Circle_2, bounded_side         )
    .METHOD(Circle_2, has_on_positive_side )
    .METHOD(Circle_2, has_on_negative_side )
    .METHOD(Circle_2, has_on_boundary      )
    .METHOD(Circle_2, has_on_bounded_side  )
    .METHOD(Circle_2, has_on_unbounded_side)
    // Miscellaneous
    .METHOD(Circle_2, opposite            )
    .METHOD(Circle_2, orthogonal_transform)
    .METHOD(Circle_2, bbox                )
    // Representation
    .REPR(Circle_2)
    ;

  direction_2
    // Creation
    .CTOR(Vector_2)
    .CTOR(Line_2)
    .CTOR(Ray_2)
    .CTOR(Segment_2)
    .CTOR(RT, RT)
    // Operations
    .METHOD(Direction_2, delta)
    .METHOD(Direction_2, dx   )
    .METHOD(Direction_2, dy   )
    .BINARY_OP_SELF(Direction_2, ==)
    .BINARY_OP_SELF(Direction_2,  <)
    .BINARY_OP_SELF(Direction_2,  >)
    .BINARY_OP_SELF(Direction_2, <=)
    .BINARY_OP_SELF(Direction_2, >=)
    .METHOD(Direction_2, counterclockwise_in_between)
    .UNARY_OP(-, Direction_2)
    // Miscellaneous
    .METHOD(Direction_2, vector   )
    .METHOD(Direction_2, transform)
    // Representation
    .REPR(Direction_2)
    ;

  iso_rectangle_2
    // Creation
    .CTOR(Point_2, Point_2)
    .CTOR(Point_2, Point_2, int)
    .CTOR(Point_2, Point_2, Point_2, Point_2)
    .CTOR(RT, RT, RT, RT)
    .CTOR(Bbox_2)
    // Operations
    .BINARY_OP_SELF(Iso_rectangle_2, ==)
    .METHOD(Iso_rectangle_2, vertex   )
    .METHOD(Iso_rectangle_2, min      )
    .METHOD(Iso_rectangle_2, max      )
    .METHOD(Iso_rectangle_2, xmin     )
    .METHOD(Iso_rectangle_2, ymin     )
    .METHOD(Iso_rectangle_2, xmax     )
    .METHOD(Iso_rectangle_2, ymax     )
    .METHOD(Iso_rectangle_2, min_coord)
    .METHOD(Iso_rectangle_2, max_coord)
    // Predicates
    .METHOD(Iso_rectangle_2, is_degenerate        )
    .METHOD(Iso_rectangle_2, bounded_side         )
    .METHOD(Iso_rectangle_2, has_on_boundary      )
    .METHOD(Iso_rectangle_2, has_on_bounded_side  )
    .METHOD(Iso_rectangle_2, has_on_unbounded_side)
    // Miscellaneous
    .METHOD(Iso_rectangle_2, area     )
    .METHOD(Iso_rectangle_2, bbox     )
    .METHOD(Iso_rectangle_2, transform)
    ;

  line_2
    // Creation
    .CTOR(RT, RT, RT)
    .CTOR(Point_2, Point_2)
    .CTOR(Point_2, Direction_2)
    .CTOR(Point_2, Vector_2)
    .CTOR(Segment_2)
    .CTOR(Ray_2)
    // Operators
    .BINARY_OP_SELF(Line_2, ==)
    .METHOD(Line_2, a         )
    .METHOD(Line_2, b         )
    .METHOD(Line_2, c         )
    .UNAMBIG_METHOD(Point_2, Line_2, point, int)
    .METHOD(Line_2, projection)
    .METHOD(Line_2, x_at_y    )
    .METHOD(Line_2, y_at_x    )
    // Predicates
    .METHOD(Line_2, is_degenerate)
    .METHOD(Line_2, is_horizontal)
    .METHOD(Line_2, is_vertical  )
    .METHOD(Line_2, oriented_side)
    // Convenience boolean functions
    .METHOD(Line_2, has_on              )
    .METHOD(Line_2, has_on_positive_side)
    .METHOD(Line_2, has_on_negative_side)
    // Miscellaneous
    .METHOD(Line_2, to_vector     )
    .METHOD(Line_2, direction     )
    .METHOD(Line_2, opposite      )
    .METHOD(Line_2, perpendicular )
    .METHOD(Line_2, transform     )
    // Representation
    .REPR(Line_2)
    ;

  point_2
    // Related Functions
    .BINARY_OP_SELF(Point_2,  <)
    .BINARY_OP_SELF(Point_2,  >)
    .BINARY_OP_SELF(Point_2, <=)
    .BINARY_OP_SELF(Point_2, >=)
    .BINARY_OP_SELF(Point_2,  -)
    .BINARY_OP(Point_2, ==, Origin )
    .BINARY_OP(Point_2, +,  Vector_2)
    .BINARY_OP(Point_2, -,  Vector_2)
    // Creation
    .CTOR(Origin)
    .CTOR(double, double)
    .CTOR(RT, RT, RT)
    .CTOR(FT, FT) // in a Cartesian kernel, covers (RT, RT) ctor
    .CTOR(Weighted_point_2)
    // Operations
    .BINARY_OP_SELF(Point_2, ==)
    // Coordinate Access
    .METHOD(Point_2, hx)
    .METHOD(Point_2, hy)
    .METHOD(Point_2, hw)
    .METHOD(Point_2, x )
    .METHOD(Point_2, y )
    // Convenience Operations
    .METHOD(Point_2, homogeneous)
    .METHOD(Point_2, cartesian  )
    // TODO: missing cartesian iteratior methods
    .METHOD(Point_2, dimension  )
    .METHOD(Point_2, bbox       )
    .METHOD(Point_2, transform  )
    // Representation
    .REPR(Point_2)
    ;

  ray_2
    // Creation
    .CTOR(Point_2, Point_2)
    .CTOR(Point_2, Direction_2)
    .CTOR(Point_2, Vector_2)
    .CTOR(Point_2, Line_2)
    // Operations
    .BINARY_OP_SELF(Ray_2, ==)
    .METHOD(Ray_2, source         )
    .METHOD(Ray_2, point          )
    .METHOD(Ray_2, direction      )
    .METHOD(Ray_2, to_vector      )
    .METHOD(Ray_2, supporting_line)
    .METHOD(Ray_2, opposite       )
    // Predicates
    .METHOD(Ray_2, is_degenerate   )
    .METHOD(Ray_2, is_horizontal   )
    .METHOD(Ray_2, is_vertical     )
    .METHOD(Ray_2, has_on          )
    .METHOD(Ray_2, collinear_has_on)
    // Miscellaneous
    .METHOD(Ray_2, transform)
    // Representation
    .REPR(Ray_2)
    ;

  segment_2
    // Creation
    .CTOR(Point_2, Point_2)
    // Operations
    .BINARY_OP_SELF(Segment_2, ==)
    .METHOD(Segment_2, source         )
    .METHOD(Segment_2, target         )
    .METHOD(Segment_2, min            )
    .METHOD(Segment_2, max            )
    .METHOD(Segment_2, vertex         )
    .METHOD(Segment_2, point          )
    .METHOD(Segment_2, squared_length )
    .METHOD(Segment_2, direction      )
    .METHOD(Segment_2, to_vector      )
    .METHOD(Segment_2, opposite       )
    .METHOD(Segment_2, supporting_line)
    // Predicates
    .METHOD(Segment_2, is_degenerate   )
    .METHOD(Segment_2, is_horizontal   )
    .METHOD(Segment_2, is_vertical     )
    .METHOD(Segment_2, has_on          )
    .METHOD(Segment_2, collinear_has_on)
    // Miscellaneous
    .METHOD(Segment_2, bbox     )
    .METHOD(Segment_2, transform)
    // Representation
    .SIMPLE_PFUNC(repr, Segment_2)
    ;

  triangle_2
    // Creation
    .CTOR(Point_2, Point_2, Point_2)
    // Operations
    .BINARY_OP_SELF(Triangle_2, ==)
    .METHOD(Triangle_2, vertex)
    // Predicates
    .METHOD(Triangle_2, is_degenerate)
    .METHOD(Triangle_2, orientation  )
    .METHOD(Triangle_2, oriented_side)
    .METHOD(Triangle_2, bounded_side )
    .METHOD(Triangle_2, has_on_positive_side )
    .METHOD(Triangle_2, has_on_negative_side )
    .METHOD(Triangle_2, has_on_boundary      )
    .METHOD(Triangle_2, has_on_bounded_side  )
    .METHOD(Triangle_2, has_on_unbounded_side)
    // Miscellaneous
    .METHOD(Triangle_2, opposite )
    .METHOD(Triangle_2, area     )
    .METHOD(Triangle_2, bbox     )
    .METHOD(Triangle_2, transform)
    ;

  vector_2
    // Public Member Functions
    .METHOD(Vector_2, squared_length)
    .BINARY_OP(Vector_2, *, FT) // in Cartesian kernel, FT = RT
    .BINARY_OP(FT, *, Vector_2) // ^ idem
    .BINARY_OP(Origin, +, Vector_2)
    // Creation
    .CTOR(Point_2, Point_2)
    .CTOR(Segment_2)
    .CTOR(Ray_2)
    .CTOR(Line_2)
    .CTOR(Null_vector)
    .CTOR(double, double)
    .CTOR(RT, RT, RT)
    .CTOR(FT, FT)
    // Coordinate Access
    .METHOD(Vector_2, hx)
    .METHOD(Vector_2, hy)
    .METHOD(Vector_2, hw)
    .METHOD(Vector_2, x )
    .METHOD(Vector_2, y )
    // Convenience Operators
    .METHOD(Vector_2, homogeneous   )
    .METHOD(Vector_2, cartesian     )
    // TODO: missing cartesian iteratior methods
    .METHOD(Vector_2, dimension     )
    .METHOD(Vector_2, direction     )
    .METHOD(Vector_2, transform     )
    .METHOD(Vector_2, perpendicular )
    // Operators
    .BINARY_OP_SELF(Vector_2, ==)
    .BINARY_OP_SELF(Vector_2,  +)
    .BINARY_OP_SELF(Vector_2,  -)
    .UNARY_OP(-, Vector_2)
    .BINARY_OP_SELF(Vector_2,  *)
    .BINARY_OP(Vector_2, /,  RT)
    //.BINARY_OP(Vector_2, *,  RT)
    //.BINARY_OP(Vector_2, *,  RT     )
    // Representation
    .REPR(Vector_2)
    ;

  weighted_point_2
    // Creation
    .CTOR(Origin)
    .CTOR(Point_2)
    .CTOR(Point_2, FT)
    .CTOR(FT, FT)
    // Bare point and weight accessor
    .METHOD(Weighted_point_2, point )
    .METHOD(Weighted_point_2, weight)
    // Operations (delegated to underlying Point_2)
    .BINARY_OP_SELF(Weighted_point_2, ==)
    .BINARY_OP_SELF(Weighted_point_2,  <)
    // Coordinate Access
    .METHOD(Weighted_point_2, hx)
    .METHOD(Weighted_point_2, hy)
    .METHOD(Weighted_point_2, hw)
    .METHOD(Weighted_point_2, x )
    .METHOD(Weighted_point_2, y )
    // Convenience Operations
    .METHOD(Weighted_point_2, homogeneous)
    .METHOD(Weighted_point_2, cartesian  )
    .METHOD(Weighted_point_2, dimension  )
    .METHOD(Weighted_point_2, bbox       )
    // Compiler doesn't like an affine transformation object with a
    // transform method with 2 arguments.. despite it being used in
    // Weighted_point_2.h.. Mind boggling
    //.METHOD(Weighted_point_2, transform  )
    .method("transform",   [](const Weighted_point_2 &wp, const Aff_transformation_2 &t) {
        return Weighted_point_2(t.transform(wp.point()), wp.weight());
    })
    // Representation
    .REPR(Weighted_point_2)
    ;

}
