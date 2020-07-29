#include <boost/variant/apply_visitor.hpp>

#include <CGAL/Kernel/global_functions.h>

#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "global_kernel_functions.hpp"
#include "macros.hpp"

#define DO_INTERSECT_2(T) \
  cgal.method("do_intersect", &do_intersect<T, Point_2>); \
  cgal.method("do_intersect", &do_intersect<T, Line_2>); \
  cgal.method("do_intersect", &do_intersect<T, Segment_2>); \
  cgal.method("do_intersect", &do_intersect<T, Ray_2>); \
  cgal.method("do_intersect", &do_intersect<T, Triangle_2>); \
  cgal.method("do_intersect", &do_intersect<T, Iso_rectangle_2>)
#define DO_INTERSECT_2_SYM \
  DO_INTERSECT_2(Point_2); \
  DO_INTERSECT_2(Line_2); \
  DO_INTERSECT_2(Segment_2); \
  DO_INTERSECT_2(Ray_2); \
  DO_INTERSECT_2(Triangle_2); \
  DO_INTERSECT_2(Iso_rectangle_2)

#define INTERSECTION_2(T) \
  cgal.method("intersection", &intersection<T, Point_2>); \
  cgal.method("intersection", &intersection<T, Line_2>); \
  cgal.method("intersection", &intersection<T, Segment_2>); \
  cgal.method("intersection", &intersection<T, Ray_2>); \
  cgal.method("intersection", &intersection<T, Triangle_2>); \
  cgal.method("intersection", &intersection<T, Iso_rectangle_2>)
#define INTERSECTION_2_SYM \
  INTERSECTION_2(Point_2); \
  INTERSECTION_2(Line_2); \
  INTERSECTION_2(Segment_2); \
  INTERSECTION_2(Ray_2); \
  INTERSECTION_2(Triangle_2); \
  INTERSECTION_2(Iso_rectangle_2)

#define DO_INTERSECT_3(T) \
  cgal.method("do_intersect", &do_intersect<T, Point_3>); \
  cgal.method("do_intersect", &do_intersect<T, Tetrahedron_3>); \
  cgal.method("do_intersect", &do_intersect<T, Segment_3>); \
  cgal.method("do_intersect", &do_intersect<T, Line_3>); \
  cgal.method("do_intersect", &do_intersect<T, Plane_3>); \
  cgal.method("do_intersect", &do_intersect<T, Triangle_3>); \
  cgal.method("do_intersect", &do_intersect<T, Ray_3>); \
  cgal.method("do_intersect", &do_intersect<T, Iso_cuboid_3>); \
  cgal.method("do_intersect", &do_intersect<T, Sphere_3>); \
  cgal.method("do_intersect", &do_intersect<T, Bbox_3>)
#define DO_INTERSECT_3_ALL \
  DO_INTERSECT_3(Point_3); \
  DO_INTERSECT_3(Tetrahedron_3); \
  DO_INTERSECT_3(Segment_3); \
  DO_INTERSECT_3(Line_3); \
  DO_INTERSECT_3(Plane_3); \
  DO_INTERSECT_3(Triangle_3); \
  DO_INTERSECT_3(Ray_3); \
  DO_INTERSECT_3(Iso_cuboid_3); \
  DO_INTERSECT_3(Sphere_3); \
  DO_INTERSECT_3(Bbox_3)

#define INTERSECTION_3(T) \
  cgal.method("intersection", &intersection<T, Point_3>); \
  cgal.method("intersection", &intersection<T, Segment_3>); \
  cgal.method("intersection", &intersection<T, Line_3>); \
  cgal.method("intersection", &intersection<T, Plane_3>); \
  cgal.method("intersection", &intersection<T, Triangle_3>); \
  cgal.method("intersection", &intersection<T, Ray_3>)
#define INTERSECTION_3_SYM \
  INTERSECTION_3(Point_3); \
  INTERSECTION_3(Segment_3); \
  INTERSECTION_3(Line_3); \
  INTERSECTION_3(Plane_3); \
  INTERSECTION_3(Triangle_3); \
  INTERSECTION_3(Ray_3)

#define SQUARED_DISTANCE_2(T) \
  cgal.method("squared_distance", &squared_distance<T, Point_2>); \
  cgal.method("squared_distance", &squared_distance<T, Line_2>); \
  cgal.method("squared_distance", &squared_distance<T, Ray_2>); \
  cgal.method("squared_distance", &squared_distance<T, Segment_2>); \
  cgal.method("squared_distance", &squared_distance<T, Triangle_2>)
#define SQUARED_DISTANCE_2_ALL \
  SQUARED_DISTANCE_2(Point_2); \
  SQUARED_DISTANCE_2(Line_2); \
  SQUARED_DISTANCE_2(Ray_2); \
  SQUARED_DISTANCE_2(Segment_2); \
  SQUARED_DISTANCE_2(Triangle_2)

#define SQUARED_DISTANCE_3(T) \
  cgal.method("squared_distance", &squared_distance<T, Point_3>); \
  cgal.method("squared_distance", &squared_distance<T, Segment_3>); \
  cgal.method("squared_distance", &squared_distance<T, Line_3>); \
  cgal.method("squared_distance", &squared_distance<T, Plane_3>); \
  cgal.method("squared_distance", &squared_distance<T, Ray_3>)
#define SQUARED_DISTANCE_3_SYM \
  SQUARED_DISTANCE_3(Point_3); \
  SQUARED_DISTANCE_3(Segment_3); \
  SQUARED_DISTANCE_3(Line_3); \
  SQUARED_DISTANCE_3(Plane_3); \
  SQUARED_DISTANCE_3(Ray_3)

namespace jlcgal {

template<typename T1, typename T2 = T1>
inline
bool
do_intersect(const T1& t1, const T2& t2) {
  return CGAL::do_intersect(t1, t2);
}

template<typename T1, typename T2 = T1>
inline
jl_value_t*
intersection(const T1& t1, const T2& t2) {
  auto result = CGAL::intersection(t1, t2);
  return result ?
    boost::apply_visitor(Intersection_visitor(), *result) :
    jl_nothing;
}

template<typename T1, typename T2 = T1>
inline
FT
squared_distance(const T1& t1, const T2& t2) {
  return CGAL::squared_distance(t1, t2);
}

void wrap_global_lk_functions(jlcxx::Module& cgal) {
  OVERRIDE_BASE(cgal,);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Vector_2&, const Vector_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_2&,  const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Vector_3&, const Vector_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_3&,  const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_3&,  const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_3&,  const Point_3&, const Point_3&, const Vector_3&);
  UNSET_OVERRIDE(cgal,);

  CGAL_GLOBAL_FUNCTION(FT, approximate_angle, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(FT, approximate_angle, const Vector_3&, const Vector_3&);

  CGAL_GLOBAL_FUNCTION(FT, approximate_dihedral_angle, const Point_3&, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(FT, area, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, are_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, are_ordered_along_line, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, are_strictly_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, are_strictly_ordered_along_line, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&);
  CGAL_GLOBAL_FUNCTION(Point_3, barycenter, const Point_3&, const FT&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, barycenter, const Point_3&, const FT&, const Point_3&, const FT&);
  CGAL_GLOBAL_FUNCTION(Point_3, barycenter, const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, barycenter, const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&, const FT&);
  CGAL_GLOBAL_FUNCTION(Point_3, barycenter, const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, barycenter, const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&, const FT&);

  CGAL_GLOBAL_FUNCTION(Line_2, bisector, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Line_2, bisector, const Line_2&,  const Line_2&);
  CGAL_GLOBAL_FUNCTION(Plane_3, bisector, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(Plane_3, bisector, const Plane_3&,  const Plane_3&);

  CGAL_GLOBAL_FUNCTION(Point_2, centroid, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, centroid, const Point_2&, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, centroid, const Triangle_2&);
  CGAL_GLOBAL_FUNCTION(Point_3, centroid, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, centroid, const Point_3&, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, centroid, const Triangle_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, centroid, const Tetrahedron_3&);

  CGAL_GLOBAL_FUNCTION(Point_2, circumcenter, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, circumcenter, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, circumcenter, const Triangle_2&);
  CGAL_GLOBAL_FUNCTION(Point_3, circumcenter, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, circumcenter, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, circumcenter, const Point_3&, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, circumcenter, const Triangle_3&);
  CGAL_GLOBAL_FUNCTION(Point_3, circumcenter, const Tetrahedron_3&);

  CGAL_GLOBAL_FUNCTION(bool, collinear_are_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, collinear_are_ordered_along_line, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, collinear_are_strictly_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, collinear_are_strictly_ordered_along_line, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, collinear, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, collinear, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_dihedral_angle, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const FT&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_dihedral_angle, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_dihedral_angle, const Vector_3&, const Vector_3&, const Vector_3&, const FT&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_dihedral_angle, const Vector_3&, const Vector_3&, const Vector_3&, const Vector_3&, const Vector_3&, const Vector_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_distance_to_point, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_distance_to_point, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_lexicographically, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_lexicographically, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_signed_distance_to_line, const Line_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_signed_distance_to_line, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_signed_distance_to_plane, const Plane_3&,  const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_signed_distance_to_plane, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_slope, const Line_2&,    const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_slope, const Segment_2&, const Segment_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_slope, const Point_3&, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_squared_distance, const Point_2&, const Point_2&, const FT&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_squared_distance, const Point_3&, const Point_3&, const FT&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_squared_radius, const Point_3&, const FT&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_squared_radius, const Point_3&, const Point_3&, const FT&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_squared_radius, const Point_3&, const Point_3&, const Point_3&, const FT&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_squared_radius, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const FT&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Point_2&, const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Line_2&,  const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Line_2&,  const Line_2&, const Line_2&, const Line_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_xy, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x_at_y, const Point_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x_at_y, const Point_2&, const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x_at_y, const Line_2&,  const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x_at_y, const Line_2&,  const Line_2&, const Line_2&, const Line_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Point_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Point_2&, const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Line_2&,  const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Line_2&,  const Line_2&, const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Point_2&, const Segment_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Point_2&, const Segment_2&, const Segment_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Point_2&, const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Line_2&,  const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Line_2&,  const Line_2&, const Line_2&, const Line_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_xyz, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_z, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_yx, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, coplanar, const Point_3&, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Orientation, coplanar_orientation, const Point_3&, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Orientation, coplanar_orientation, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Bounded_side, coplanar_side_of_bounded_circle, const Point_3&, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(Vector_3, cross_product, const Vector_3&, const Vector_3&);

  CGAL_GLOBAL_FUNCTION(FT, determinant, const Vector_2&, const Vector_2&);
  CGAL_GLOBAL_FUNCTION(FT, determinant, const Vector_3&, const Vector_3&, const Vector_3&);

  DO_INTERSECT_2_SYM;
  cgal.method("do_intersect", &do_intersect<Circle_2>);
  cgal.method("do_intersect", &do_intersect<Circle_2, Point_2>);
  cgal.method("do_intersect", &do_intersect<Circle_2, Line_2>);
  cgal.method("do_intersect", &do_intersect<Circle_2, Iso_rectangle_2>);
  cgal.method("do_intersect", &do_intersect<Circle_2, Bbox_2>);
  cgal.method("do_intersect", &do_intersect<Bbox_2, Point_2>);
  cgal.method("do_intersect", &do_intersect<Bbox_2, Line_2>);
  cgal.method("do_intersect", &do_intersect<Bbox_2, Ray_2>);
  cgal.method("do_intersect", &do_intersect<Bbox_2, Circle_2>);
  cgal.method("do_intersect", &do_intersect<Point_2, Circle_2>);
  cgal.method("do_intersect", &do_intersect<Point_2, Bbox_2>);
  cgal.method("do_intersect", &do_intersect<Line_2, Circle_2>);
  cgal.method("do_intersect", &do_intersect<Line_2, Bbox_2>);
  cgal.method("do_intersect", &do_intersect<Ray_2, Bbox_2>);
  cgal.method("do_intersect", &do_intersect<Iso_rectangle_2, Circle_2>);

  DO_INTERSECT_3_ALL;

  CGAL_GLOBAL_FUNCTION(bool, has_larger_distance_to_point, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, has_larger_distance_to_point, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, has_larger_signed_distance_to_line, const Line_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, has_larger_signed_distance_to_line, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, has_larger_signed_distance_to_plane, const Plane_3&,  const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(bool, has_larger_signed_distance_to_plane, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, has_smaller_distance_to_point, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, has_smaller_distance_to_point, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, has_smaller_signed_distance_to_line, const Line_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, has_smaller_signed_distance_to_line, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, has_smaller_signed_distance_to_plane, const Plane_3&,  const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(bool, has_smaller_signed_distance_to_plane, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&);

  INTERSECTION_2_SYM;
  cgal.method("intersection", &intersection<Point_2, Circle_2>);
  cgal.method("intersection", &intersection<Circle_2, Point_2>);
  cgal.method("intersection", &intersection<Point_2, Bbox_2>);
  cgal.method("intersection", &intersection<Bbox_2, Point_2>);

  INTERSECTION_3_SYM;
  cgal.method("intersection", &intersection<Point_3, Tetrahedron_3>);
  cgal.method("intersection", &intersection<Point_3, Iso_cuboid_3>);
  cgal.method("intersection", &intersection<Point_3, Sphere_3>);
  cgal.method("intersection", &intersection<Point_3, Bbox_3>);
  cgal.method("intersection", &intersection<Tetrahedron_3, Point_3>);
  cgal.method("intersection", &intersection<Segment_3, Iso_cuboid_3>);
  cgal.method("intersection", &intersection<Segment_3, Bbox_3>);
  cgal.method("intersection", &intersection<Line_3, Iso_cuboid_3>);
  cgal.method("intersection", &intersection<Line_3, Bbox_3>);
  cgal.method("intersection", &intersection<Plane_3, Sphere_3>);
  cgal.method("intersection", &intersection<Triangle_3, Iso_cuboid_3>);
  cgal.method("intersection", &intersection<Ray_3, Iso_cuboid_3>);
  cgal.method("intersection", &intersection<Ray_3, Bbox_3>);
  cgal.method("intersection", &intersection<Iso_cuboid_3>);
  cgal.method("intersection", &intersection<Iso_cuboid_3, Point_3>);
  cgal.method("intersection", &intersection<Iso_cuboid_3, Segment_3>);
  cgal.method("intersection", &intersection<Iso_cuboid_3, Line_3>);
  cgal.method("intersection", &intersection<Iso_cuboid_3, Triangle_3>);
  cgal.method("intersection", &intersection<Iso_cuboid_3, Ray_3>);
  cgal.method("intersection", &intersection<Sphere_3>);
  cgal.method("intersection", &intersection<Sphere_3, Point_3>);
  cgal.method("intersection", &intersection<Sphere_3, Plane_3>);
  cgal.method("intersection", &intersection<Bbox_3, Point_3>);
  cgal.method("intersection", &intersection<Bbox_3, Segment_3>);
  cgal.method("intersection", &intersection<Bbox_3, Line_3>);
  cgal.method("intersection", &intersection<Bbox_3, Ray_3>);

  CGAL_GLOBAL_FUNCTION(FT, l_infinity_distance, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(FT, l_infinity_distance, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, left_turn, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xy_larger, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xy_larger_or_equal, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xy_smaller, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xy_smaller_or_equal, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xyz_smaller, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xyz_smaller_or_equal, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(Point_2, max_vertex, const Iso_rectangle_2&);
  CGAL_GLOBAL_FUNCTION(Point_3, max_vertex, const Iso_cuboid_3&);

  CGAL_GLOBAL_FUNCTION(Point_2, midpoint, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_3, midpoint, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(Point_2, min_vertex, const Iso_rectangle_2&);
  CGAL_GLOBAL_FUNCTION(Point_3, min_vertex, const Iso_cuboid_3&);

  CGAL_GLOBAL_FUNCTION(Vector_3, normal, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Orientation, orientation, const Point_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Orientation, orientation, const Vector_2&, const Vector_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Orientation, orientation, const Point_3&,  const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Orientation, orientation, const Vector_3&, const Vector_3&, const Vector_3&);

  CGAL_GLOBAL_FUNCTION(Vector_3, orthogonal_vector, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, parallel, const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(bool, parallel, const Ray_2&, const Ray_2&);
  CGAL_GLOBAL_FUNCTION(bool, parallel, const Segment_2&, const Segment_2&);
  CGAL_GLOBAL_FUNCTION(bool, parallel, const Line_3&, const Line_3&);
  CGAL_GLOBAL_FUNCTION(bool, parallel, const Plane_3&, const Plane_3&);
  CGAL_GLOBAL_FUNCTION(bool, parallel, const Ray_3&, const Ray_3&);
  CGAL_GLOBAL_FUNCTION(bool, parallel, const Segment_3&, const Segment_3&);

  CGAL_GLOBAL_FUNCTION(Plane_3, radical_plane, const Sphere_3&, const Sphere_3&);

  CGAL_GLOBAL_FUNCTION(Line_2, radical_line, const Circle_2&, const Circle_2&);

  CGAL_GLOBAL_FUNCTION(void, rational_rotation_approximation, const RT&, const RT&, RT&, RT&, RT&, const RT&, const RT&);

  CGAL_GLOBAL_FUNCTION(bool, right_turn, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(FT, scalar_product, const Vector_2&, const Vector_2&);
  CGAL_GLOBAL_FUNCTION(FT, scalar_product, const Vector_3&, const Vector_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Bounded_side, side_of_bounded_circle, const Point_2&, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Bounded_side, side_of_bounded_circle, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Bounded_side, side_of_bounded_sphere, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Bounded_side, side_of_bounded_sphere, const Point_3&, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(CGAL::Bounded_side, side_of_bounded_sphere, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(CGAL::Oriented_side, side_of_oriented_circle, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Oriented_side, side_of_oriented_sphere, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(FT, squared_area, const Point_3&, const Point_3&, const Point_3&);

  SQUARED_DISTANCE_2_ALL;

  SQUARED_DISTANCE_3_SYM;
  cgal.method("squared_distance", &squared_distance<Point_3, Triangle_3>);
  cgal.method("squared_distance", &squared_distance<Triangle_3, Point_3>);

  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_2&);
  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_3&, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_3&, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_3&);

  CGAL_GLOBAL_FUNCTION(Vector_3, unit_normal, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(FT, volume, const Point_3&, const Point_3&, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, x_equal, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, x_equal, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(bool, y_equal, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, y_equal, const Point_3&, const Point_3&);
  CGAL_GLOBAL_FUNCTION(bool, z_equal, const Point_3&, const Point_3&);

  CGAL_GLOBAL_FUNCTION(bool, do_overlap, const Bbox_2&, const Bbox_2&);
  CGAL_GLOBAL_FUNCTION(bool, do_overlap, const Bbox_3&, const Bbox_3&);
}

} // jlcgal

#undef DO_INTERSECT_2
#undef DO_INTERSECT_2_SYM

#undef INTERSECTION_2
#undef INTERSECTION_2_SYM

#undef DO_INTERSECT_3
#undef DO_INTERSECT_3_ALL

#undef INTERSECTION_3
#undef INTERSECTION_3_SYM

#undef SQUARED_DISTANCE_2
#undef SQUARED_DISTANCE_2_ALL

#undef SQUARED_DISTANCE_3
#undef SQUARED_DISTANCE_3_SYM
