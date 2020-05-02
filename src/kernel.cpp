#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

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

void wrap_aff_transformation_2(jlcxx::Module&, jlcxx::TypeWrapper<Aff_transformation_2>&);
void wrap_bbox_2(jlcxx::Module&, jlcxx::TypeWrapper<Bbox_2>&);
void wrap_circle_2(jlcxx::Module&, jlcxx::TypeWrapper<Circle_2>&);
void wrap_direction_2(jlcxx::Module&, jlcxx::TypeWrapper<Direction_2>&);
void wrap_iso_rectangle_2(jlcxx::Module&, jlcxx::TypeWrapper<Iso_rectangle_2>&);
void wrap_line_2(jlcxx::Module&, jlcxx::TypeWrapper<Line_2>&);
void wrap_point_2(jlcxx::Module&, jlcxx::TypeWrapper<Point_2>&);
void wrap_ray_2(jlcxx::Module&, jlcxx::TypeWrapper<Ray_2>&);
void wrap_segment_2(jlcxx::Module&, jlcxx::TypeWrapper<Segment_2>&);
void wrap_triangle_2(jlcxx::Module&, jlcxx::TypeWrapper<Triangle_2>&);
void wrap_vector_2(jlcxx::Module&, jlcxx::TypeWrapper<Vector_2>&);
void wrap_weighted_point_2(jlcxx::Module&, jlcxx::TypeWrapper<Weighted_point_2>&);

void wrap_plane_3(jlcxx::Module&, jlcxx::TypeWrapper<Plane_3>&);
void wrap_point_3(jlcxx::Module&, jlcxx::TypeWrapper<Point_3>&);
void wrap_segment_3(jlcxx::Module&, jlcxx::TypeWrapper<Segment_3>&);
void wrap_vector_3(jlcxx::Module&, jlcxx::TypeWrapper<Vector_3>&);

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
    .REPR(FT)
    ;
#endif

  // 2D
  auto aff_transformation_2 = cgal.add_type<Aff_transformation_2>("AffTransformation2");
  auto bbox_2               = cgal.add_type<Bbox_2>              ("Bbox2");
  auto circle_2             = cgal.add_type<Circle_2>            ("Circle2");
  auto direction_2          = cgal.add_type<Direction_2>         ("Direction2");
  auto iso_rectangle_2      = cgal.add_type<Iso_rectangle_2>     ("IsoRectangle2");
  auto line_2               = cgal.add_type<Line_2>              ("Line2");
  auto point_2              = cgal.add_type<Point_2>             ("Point2");
  auto ray_2                = cgal.add_type<Ray_2>               ("Ray2");
  auto segment_2            = cgal.add_type<Segment_2>           ("Segment2");
  auto triangle_2           = cgal.add_type<Triangle_2>          ("Triangle2");
  auto vector_2             = cgal.add_type<Vector_2>            ("Vector2");
  auto weighted_point_2     = cgal.add_type<Weighted_point_2>    ("WeightedPoint2");

  wrap_bbox_2(cgal, bbox_2);
  wrap_point_2(cgal, point_2);
  wrap_vector_2(cgal, vector_2);
  wrap_circle_2(cgal, circle_2);
  wrap_direction_2(cgal, direction_2);
  wrap_iso_rectangle_2(cgal, iso_rectangle_2);
  wrap_line_2(cgal, line_2);
  wrap_ray_2(cgal, ray_2);
  wrap_segment_2(cgal, segment_2);
  wrap_triangle_2(cgal, triangle_2);
  wrap_weighted_point_2(cgal, weighted_point_2);
  wrap_aff_transformation_2(cgal, aff_transformation_2);

  // 3D
  auto plane_3              = cgal.add_type<Plane_3>             ("Plane3");
  auto point_3              = cgal.add_type<Point_3>             ("Point3");
  auto segment_3            = cgal.add_type<Segment_3>           ("Segment3");
  auto vector_3             = cgal.add_type<Vector_3>            ("Vector3");

  wrap_plane_3(cgal, plane_3);
  wrap_point_3(cgal, point_3);
  wrap_segment_3(cgal, segment_3);
  wrap_vector_3(cgal, vector_3);
}
