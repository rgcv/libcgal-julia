#include <type_traits>

#include <CGAL/Origin.h>
#include <CGAL/aff_transformation_tags.h>
#include <CGAL/enum.h>

#include <jlcxx/module.hpp>
#include <jlcxx/type_conversion.hpp>

#include <julia/julia.h>

#include "io.hpp"
#include "macros.hpp"

#include "kernel.hpp"

template<> struct jlcxx::IsMirroredType<CGAL::Identity_transformation> : std::false_type {};
template<> struct jlcxx::IsMirroredType<CGAL::Rotation>                : std::false_type {};
template<> struct jlcxx::IsMirroredType<CGAL::Scaling>                 : std::false_type {};
template<> struct jlcxx::IsMirroredType<CGAL::Translation>             : std::false_type {};

void wrap_kernel(jlcxx::Module& cgal) {
  /// TYPES ====================================================================

  auto field_type = cgal.add_type<FT>("FieldType", jlcxx::julia_type("Real"));

  auto aff_transformation_2 = cgal.TYPE(Aff_transformation_2, AffTransformation2);
  auto bbox_2 = cgal.TYPE(Bbox_2, BBox2);
  auto circle_2 = cgal.TYPE(Circle_2, Circle2);
  auto direction_2 = cgal.TYPE(Direction_2, Direction2);
  auto iso_rectangle_2 = cgal.TYPE(Iso_rectangle_2, IsoRectangle2);
  auto line_2 = cgal.TYPE(Line_2, Line2);
  auto point_2 = cgal.TYPE(Point_2, Point2);
  auto ray_2 = cgal.TYPE(Ray_2, Ray2);
  auto segment_2 = cgal.TYPE(Segment_2, Segment2);
  auto triangle_2 = cgal.TYPE(Triangle_2, Triangle2);
  auto vector_2 = cgal.TYPE(Vector_2, Vector2);
  auto weighted_point_2 = cgal.TYPE(Weighted_point_2, WeightedPoint2);

  /// CONSTANTS ================================================================

  // Can't set consts, they get erased post pre-compilation.
  // Therefore, their constant counterparts are defined on the julia side.
  CGAL_TYPE(Identity_transformation, IdentityTransformation);
  CGAL_STYPE(Rotation);
  CGAL_STYPE(Scaling);
  CGAL_STYPE(Translation);

  /// TYPES (cont.) ============================================================

  field_type
    // Creation
    .CTOR(double)
    OVERRIDE_BASE(cgal, field_type)
    // RealEmbeddable Operations
    .BINARY_OP_SELF(const FT&, ==)
    .BINARY_OP_SELF(const FT&,  <)
    .BINARY_OP_SELF(const FT&, <=)
    .BINARY_OP_SELF(const FT&,  >)
    .BINARY_OP_SELF(const FT&, >=)
    // Field Operations
    .BINARY_OP_SELF(const FT&, /)
    // IntegralDomainWithoutDivision Operations
    .BINARY_OP_SELF(const FT&, +)
    .BINARY_OP_SELF(const FT&, -)
    .BINARY_OP_SELF(const FT&, *)
    .UNARY_OP(+, const FT&)
    .UNARY_OP(-, const FT&)
    UNSET_OVERRIDE(cgal, field_type)
    // Representation
    .REPR(FT)
    ;

  aff_transformation_2
    // Creation
    .CTOR(const CGAL::Identity_transformation&)
    .CTOR(const CGAL::Translation&, const Vector_2&)
    .CTOR(const CGAL::Rotation&, const Direction_2&, const RT&)
    .CTOR(const CGAL::Rotation&, const Direction_2&, const RT&, const RT&)
    .CTOR(const CGAL::Rotation&, const RT&, const RT&)
    .CTOR(const CGAL::Rotation&, const RT&, const RT&, const RT&)
    .CTOR(const CGAL::Scaling&, const RT&)
    .CTOR(const CGAL::Scaling&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&, const RT&)
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
    OVERRIDE_BASE(cgal, aff_transformation_2)
    .BINARY_OP_SELF(const Aff_transformation_2&, ==)
    .BINARY_OP_SELF(const Aff_transformation_2&,  *)
    UNSET_OVERRIDE(cgal, aff_transformation_2)
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
    .METHOD(Bbox_2, dimension)
    .METHOD(Bbox_2, xmin     )
    .METHOD(Bbox_2, ymin     )
    .METHOD(Bbox_2, xmax     )
    .METHOD(Bbox_2, ymax     )
    OVERRIDE_BASE(cgal, bbox_2)
    .BINARY_OP_SELF(const Bbox_2&, ==)
    .BINARY_OP_SELF(const Bbox_2&,  +)
    .METHOD(Bbox_2, min      )
    .METHOD(Bbox_2, max      )
    UNSET_OVERRIDE(cgal, bbox_2)
    .METHOD(Bbox_2, dilate   )
    // Representation
    .REPR(Bbox_2)
    ;

  circle_2
    // Creation
    .CTOR(const Point_2&, double)
    .CTOR(const Point_2&, const FT&)
    .CTOR(const Point_2&, const FT&, const CGAL::Orientation&)
    .CTOR(const Point_2&, const Point_2&, Point_2)
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Point_2&, const Point_2&, const CGAL::Orientation&)
    .CTOR(const Point_2&)
    .CTOR(const Point_2&, const CGAL::Orientation&)
    // Access Functions
    .METHOD(Circle_2, center        )
    .METHOD(Circle_2, squared_radius)
    .METHOD(Circle_2, orientation   )
    OVERRIDE_BASE(cgal, circle_2)
    .BINARY_OP_SELF(const Circle_2&, ==)
    UNSET_OVERRIDE(cgal, circle_2)
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
    .CTOR(const Vector_2&)
    .CTOR(const Line_2&)
    .CTOR(const Ray_2&)
    .CTOR(const Segment_2&)
    .CTOR(const RT&, const RT&)
    // Operations
    .METHOD(Direction_2, delta)
    .METHOD(Direction_2, dx   )
    .METHOD(Direction_2, dy   )
    .METHOD(Direction_2, counterclockwise_in_between)
    OVERRIDE_BASE(cgal, direction_2)
    .BINARY_OP_SELF(const Direction_2&, ==)
    .BINARY_OP_SELF(const Direction_2&,  <)
    .BINARY_OP_SELF(const Direction_2&,  >)
    .BINARY_OP_SELF(const Direction_2&, <=)
    .BINARY_OP_SELF(const Direction_2&, >=)
    .UNARY_OP(-, const Direction_2&)
    UNSET_OVERRIDE(cgal, direction_2)
    // Miscellaneous
    .METHOD(Direction_2, vector   )
    .METHOD(Direction_2, transform)
    // Representation
    .REPR(Direction_2)
    ;

  iso_rectangle_2
    // Creation
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Point_2&, const Point_2&, int)
    .CTOR(const Point_2&, const Point_2&, const Point_2&, const Point_2&)
    .CTOR(const RT&, const RT&, const RT&, const RT&)
    .CTOR(const Bbox_2&)
    // Operations
    OVERRIDE_BASE(cgal, iso_rectangle_2)
    .BINARY_OP_SELF(const Iso_rectangle_2&, ==)
    .METHOD(Iso_rectangle_2, min      )
    .METHOD(Iso_rectangle_2, max      )
    UNSET_OVERRIDE(cgal, iso_rectangle_2)
    .METHOD(Iso_rectangle_2, vertex   )
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
    // Representation
    .REPR(Iso_rectangle_2)
    ;

  line_2
    // Creation
    .CTOR(const RT&, const RT&, const RT&)
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Point_2&, const Direction_2&)
    .CTOR(const Point_2&, const Vector_2&)
    .CTOR(const Segment_2&)
    .CTOR(const Ray_2&)
    // Operators
    OVERRIDE_BASE(cgal, line_2)
    .BINARY_OP_SELF(const Line_2&, ==)
    UNSET_OVERRIDE(cgal, line_2)
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
    OVERRIDE_BASE(cgal, point_2)
    .BINARY_OP_SELF(const Point_2&,  <)
    .BINARY_OP_SELF(const Point_2&,  >)
    .BINARY_OP_SELF(const Point_2&, <=)
    .BINARY_OP_SELF(const Point_2&, >=)
    .BINARY_OP_SELF(const Point_2&,  -)
    .BINARY_OP_SELF(const Point_2&, ==)
    .BINARY_OP(const Point_2&, ==, CGAL::Origin)
    .BINARY_OP(const Point_2&, +,  Vector_2    )
    .BINARY_OP(const Point_2&, -,  Vector_2    )
    UNSET_OVERRIDE(cgal, point_2)
    // Creation
    .CTOR(const CGAL::Origin&)
    .CTOR(double, double)
    .CTOR(const RT&, const RT&, const RT&)
    .CTOR(const FT&, const FT&) // in a Cartesian kernel, covers (RT, RT) ctor
    .CTOR(const Weighted_point_2&)
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
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Point_2&, const Direction_2&)
    .CTOR(const Point_2&, const Vector_2&)
    .CTOR(const Point_2&, const Line_2&)
    // Operations
    OVERRIDE_BASE(cgal, ray_2)
    .BINARY_OP_SELF(const Ray_2&, ==)
    UNSET_OVERRIDE(cgal, ray_2)
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
    .CTOR(const Point_2&, const Point_2&)
    // Operations
    OVERRIDE_BASE(cgal, segment_2)
    .BINARY_OP_SELF(const Segment_2&, ==)
    .METHOD(Segment_2, min)
    .METHOD(Segment_2, max)
    UNSET_OVERRIDE(cgal, segment_2)
    .METHOD(Segment_2, source         )
    .METHOD(Segment_2, target         )
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
    .REPR(Segment_2)
    ;

  triangle_2
    // Creation
    .CTOR(const Point_2&, const Point_2&, const Point_2&)
    // Operations
    OVERRIDE_BASE(cgal, triangle_2)
    .BINARY_OP_SELF(const Triangle_2&, ==)
    UNSET_OVERRIDE(cgal, triangle_2)
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
    // Representation
    .REPR(Triangle_2)
    ;

  vector_2
    // Public Member Functions
    .METHOD(Vector_2, squared_length)
    OVERRIDE_BASE(cgal, vector_2)
    .BINARY_OP(const Vector_2&,     *, const RT&) // in Cartesian kernel, FT = RT
    .BINARY_OP(const RT&,           *, const Vector_2&) // ^ idem
    .BINARY_OP(const CGAL::Origin&, +, const Vector_2&)
    UNSET_OVERRIDE(cgal, vector_2)
    // Creation
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Segment_2&)
    .CTOR(const Ray_2&)
    .CTOR(const Line_2&)
    .CTOR(const CGAL::Null_vector&)
    .CTOR(double, double)
    .CTOR(const RT&, const RT&, const RT&)
    .CTOR(const FT&, const FT&)
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
    OVERRIDE_BASE(cgal, vector_2)
    .BINARY_OP_SELF(const Vector_2&, ==)
    .BINARY_OP_SELF(const Vector_2&,  +)
    .BINARY_OP_SELF(const Vector_2&,  -)
    .UNARY_OP(-, const Vector_2&)
    .BINARY_OP_SELF(const Vector_2&,  *)
    .BINARY_OP(const Vector_2&, /,  const RT&)
    UNSET_OVERRIDE(cgal, vector_2)
    //.BINARY_OP(Vector_2, *,  RT)
    //.BINARY_OP(Vector_2, *,  RT     )
    // Representation
    .REPR(Vector_2)
    ;

  weighted_point_2
    // Creation
    .CTOR(const CGAL::Origin&)
    .CTOR(const Point_2&)
    .CTOR(const Point_2&, const FT&)
    .CTOR(const FT&, const FT&)
    // Bare point and weight accessor
    .METHOD(Weighted_point_2, point )
    .METHOD(Weighted_point_2, weight)
    // Operations (delegated to underlying Point_2)
    OVERRIDE_BASE(cgal, weighted_point_2)
    .BINARY_OP_SELF(const Weighted_point_2&, ==)
    .BINARY_OP_SELF(const Weighted_point_2&,  <)
    UNSET_OVERRIDE(cgal, weighted_point_2)
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
