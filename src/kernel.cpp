#include <CGAL/Origin.h>
#include <CGAL/enum.h>

#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"
#include "macros.hpp"

#define OPERATION(T, op) \
   BINARY_OP(     T, op, double) \
  .BINARY_OP(double, op,      T) \
  .BINARY_OP_SELF(T, op)

#define OPERATORS(T) \
  /* RealEmbeddable Operations */ \
   OPERATION(T, ==) \
  .OPERATION(T,  <) \
  .OPERATION(T, <=) \
  .OPERATION(T,  >) \
  .OPERATION(T, >=) \
  /* Field Operations */ \
  /* .OPERATION(T, /) */ \
  /* IntegralDomainWithoutDivision Operations */ \
  .OPERATION(T, +) \
  .OPERATION(T, -) \
  .OPERATION(T, *) \
  .UNARY_OP(+, T) \
  .UNARY_OP(-, T)

#define CGAL_CONST(N)   cgal.set_const(#N, CGAL::N)
#define CGAL_ENUM(E, N) cgal.add_bits<CGAL::E>(#N, jlcxx::julia_type("CppEnum"))
#define CGAL_SENUM(E)   CGAL_ENUM(E, E)

namespace jlcgal {

void wrap_aff_transformation_2(jlcxx::Module&, jlcxx::TypeWrapper<Aff_transformation_2>&);
void wrap_bbox_2(jlcxx::Module&, jlcxx::TypeWrapper<Bbox_2>&);
void wrap_circle_2(jlcxx::Module&, jlcxx::TypeWrapper<Circle_2>&);
void wrap_circular_arc_2(jlcxx::Module&, jlcxx::TypeWrapper<Circular_arc_2>&);
void wrap_direction_2(jlcxx::Module&, jlcxx::TypeWrapper<Direction_2>&);
void wrap_iso_rectangle_2(jlcxx::Module&, jlcxx::TypeWrapper<Iso_rectangle_2>&);
void wrap_line_2(jlcxx::Module&, jlcxx::TypeWrapper<Line_2>&);
void wrap_point_2(jlcxx::Module&, jlcxx::TypeWrapper<Point_2>&);
void wrap_ray_2(jlcxx::Module&, jlcxx::TypeWrapper<Ray_2>&);
void wrap_segment_2(jlcxx::Module&, jlcxx::TypeWrapper<Segment_2>&);
void wrap_triangle_2(jlcxx::Module&, jlcxx::TypeWrapper<Triangle_2>&);
void wrap_vector_2(jlcxx::Module&, jlcxx::TypeWrapper<Vector_2>&);
void wrap_weighted_point_2(jlcxx::Module&, jlcxx::TypeWrapper<Weighted_point_2>&);

void wrap_aff_transformation_3(jlcxx::Module&, jlcxx::TypeWrapper<Aff_transformation_3>&);
void wrap_bbox_3(jlcxx::Module&, jlcxx::TypeWrapper<Bbox_3>&);
void wrap_circle_3(jlcxx::Module&, jlcxx::TypeWrapper<Circle_3>&);
void wrap_circular_arc_3(jlcxx::Module&, jlcxx::TypeWrapper<Circular_arc_3>&);
void wrap_direction_3(jlcxx::Module&, jlcxx::TypeWrapper<Direction_3>&);
void wrap_iso_cuboid_3(jlcxx::Module&, jlcxx::TypeWrapper<Iso_cuboid_3>&);
void wrap_line_3(jlcxx::Module&, jlcxx::TypeWrapper<Line_3>&);
void wrap_plane_3(jlcxx::Module&, jlcxx::TypeWrapper<Plane_3>&);
void wrap_point_3(jlcxx::Module&, jlcxx::TypeWrapper<Point_3>&);
void wrap_ray_3(jlcxx::Module&, jlcxx::TypeWrapper<Ray_3>&);
void wrap_segment_3(jlcxx::Module&, jlcxx::TypeWrapper<Segment_3>&);
void wrap_sphere_3(jlcxx::Module&, jlcxx::TypeWrapper<Sphere_3>&);
void wrap_tetrahedron_3(jlcxx::Module&, jlcxx::TypeWrapper<Tetrahedron_3>&);
void wrap_triangle_3(jlcxx::Module&, jlcxx::TypeWrapper<Triangle_3>&);
void wrap_vector_3(jlcxx::Module&, jlcxx::TypeWrapper<Vector_3>&);
void wrap_weighted_point_3(jlcxx::Module&, jlcxx::TypeWrapper<Weighted_point_3>&);

void wrap_kernel(jlcxx::Module& cgal) {
#ifdef JLCGAL_EXACT_CONSTRUCTIONS
  auto field_type = cgal.add_type<FT>("FieldType", jlcxx::julia_type("Real"))
    // Creation
    .CTOR(double)
    OVERRIDE_BASE(cgal, field_type)
    .OPERATORS(const FT&)
    .method("/", &safe_division<FT, FT>)
    .method("/", &safe_division<FT, double>)
    .method("/", &safe_division<double, FT>)
    UNSET_OVERRIDE(cgal, field_type)
    // Representation
    .TO_STRING(FT)
    ;
#endif

  /// Origin / Null_vector
  cgal.map_type<CGAL::Origin>("Origin");
  cgal.map_type<CGAL::Null_vector>("NullVector");

  /// Enums
  CGAL_SENUM(Sign);
  // Sign
  CGAL_CONST(NEGATIVE ); CGAL_CONST(ZERO    ); CGAL_CONST(POSITIVE  );
  CGAL_CONST(COLLINEAR); CGAL_CONST(COPLANAR); CGAL_CONST(DEGENERATE);
  // Orientation
  CGAL_CONST(RIGHT_TURN); CGAL_CONST(LEFT_TURN);
  CGAL_CONST(CLOCKWISE ); CGAL_CONST(COUNTERCLOCKWISE);
  // Oriented_side
  CGAL_CONST(ON_NEGATIVE_SIDE); CGAL_CONST(ON_ORIENTED_BOUNDARY); CGAL_CONST(ON_POSITIVE_SIDE);
  // Comparison_result
  CGAL_CONST(SMALLER); CGAL_CONST(EQUAL); CGAL_CONST(LARGER);

  CGAL_ENUM(Bounded_side, BoundedSide);
  /* CGAL_UNAMBIG_FUNC(CGAL::Bounded_side, opposite, CGAL::Bounded_side); */
  CGAL_CONST(ON_UNBOUNDED_SIDE); CGAL_CONST(ON_BOUNDARY); CGAL_CONST(ON_BOUNDED_SIDE);

  CGAL_SENUM(Angle);
  /* CGAL_UNAMBIG_FUNC(CGAL::Angle, opposite, CGAL::Angle); */
  CGAL_CONST(OBTUSE); CGAL_CONST(RIGHT); CGAL_CONST(ACUTE);

  CGAL_ENUM(Box_parameter_space_2, BoxParameterSpace2);
  CGAL_CONST(LEFT_BOUNDARY  ); CGAL_CONST(RIGHT_BOUNDARY);
  CGAL_CONST(BOTTOM_BOUNDARY); CGAL_CONST(TOP_BOUNDARY  );
  CGAL_CONST(INTERIOR       ); CGAL_CONST(EXTERIOR      );

  /// 2D
  auto aff_transformation_2 = cgal.add_type<Aff_transformation_2>("AffTransformation2");
  auto bbox_2               = cgal.add_type<Bbox_2>              ("Bbox2");
  auto circle_2             = cgal.add_type<Circle_2>            ("Circle2");
  auto circular_arc_2       = cgal.add_type<Circular_arc_2>      ("CircularArc2");
  auto direction_2          = cgal.add_type<Direction_2>         ("Direction2");
  auto iso_rectangle_2      = cgal.add_type<Iso_rectangle_2>     ("IsoRectangle2");
  auto line_2               = cgal.add_type<Line_2>              ("Line2");
  auto point_2              = cgal.add_type<Point_2>             ("Point2");
  auto ray_2                = cgal.add_type<Ray_2>               ("Ray2");
  auto segment_2            = cgal.add_type<Segment_2>           ("Segment2");
  auto triangle_2           = cgal.add_type<Triangle_2>          ("Triangle2");
  auto vector_2             = cgal.add_type<Vector_2>            ("Vector2");
  auto weighted_point_2     = cgal.add_type<Weighted_point_2>    ("WeightedPoint2");

  wrap_aff_transformation_2(cgal, aff_transformation_2);
  wrap_bbox_2(cgal, bbox_2);
  wrap_point_2(cgal, point_2);
  wrap_vector_2(cgal, vector_2);
  wrap_circle_2(cgal, circle_2);
  wrap_circular_arc_2(cgal, circular_arc_2);
  wrap_direction_2(cgal, direction_2);
  wrap_iso_rectangle_2(cgal, iso_rectangle_2);
  wrap_line_2(cgal, line_2);
  wrap_ray_2(cgal, ray_2);
  wrap_segment_2(cgal, segment_2);
  wrap_triangle_2(cgal, triangle_2);
  wrap_weighted_point_2(cgal, weighted_point_2);

  /// 3D
  auto aff_transformation_3 = cgal.add_type<Aff_transformation_3>("AffTransformation3");
  auto bbox_3               = cgal.add_type<Bbox_3>              ("Bbox3");
  auto circle_3             = cgal.add_type<Circle_3>            ("Circle3");
  auto circular_arc_3       = cgal.add_type<Circular_arc_3>      ("CircularArc3");
  auto direction_3          = cgal.add_type<Direction_3>         ("Direction3");
  auto iso_cuboid_3         = cgal.add_type<Iso_cuboid_3>        ("IsoCuboid3");
  auto line_3               = cgal.add_type<Line_3>              ("Line3");
  auto plane_3              = cgal.add_type<Plane_3>             ("Plane3");
  auto point_3              = cgal.add_type<Point_3>             ("Point3");
  auto ray_3                = cgal.add_type<Ray_3>               ("Ray3");
  auto segment_3            = cgal.add_type<Segment_3>           ("Segment3");
  auto sphere_3             = cgal.add_type<Sphere_3>            ("Sphere3");
  auto tetrahedron_3        = cgal.add_type<Tetrahedron_3>       ("Tetrahedron3");
  auto triangle_3           = cgal.add_type<Triangle_3>          ("Triangle3");
  auto vector_3             = cgal.add_type<Vector_3>            ("Vector3");
  auto weighted_point_3     = cgal.add_type<Weighted_point_3>    ("WeightedPoint3");

  wrap_aff_transformation_3(cgal, aff_transformation_3);
  wrap_bbox_3(cgal, bbox_3);
  wrap_circle_3(cgal, circle_3);
  wrap_circular_arc_3(cgal, circular_arc_3);
  wrap_direction_3(cgal, direction_3);
  wrap_iso_cuboid_3(cgal, iso_cuboid_3);
  wrap_line_3(cgal, line_3);
  wrap_plane_3(cgal, plane_3);
  wrap_point_3(cgal, point_3);
  wrap_ray_3(cgal, ray_3);
  wrap_segment_3(cgal, segment_3);
  wrap_sphere_3(cgal, sphere_3);
  wrap_tetrahedron_3(cgal, tetrahedron_3);
  wrap_triangle_3(cgal, triangle_3);
  wrap_vector_3(cgal, vector_3);
  wrap_weighted_point_3(cgal, weighted_point_3);
}

} // jlcgal

#undef OPERATION
#undef OPERATORS

#undef CGAL_CONST
#undef CGAL_ENUM
#undef CGAL_SENUM
