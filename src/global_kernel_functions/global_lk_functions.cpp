#include <boost/variant/apply_visitor.hpp>

#include <CGAL/Kernel/global_functions.h>

#include <jlcxx/module.hpp>

#include <julia.h>

#include "global_kernel_functions.hpp"
#include "kernel.hpp"

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
  cgal.set_override_module(jl_base_module);
  cgal.method("angle", static_cast<CGAL::Angle(*)(const Vector_2&, const Vector_2&)>(&CGAL::angle));
  cgal.method("angle", static_cast<CGAL::Angle(*)(const Point_2&,  const Point_2&, const Point_2&)>(&CGAL::angle));
  cgal.method("angle", static_cast<CGAL::Angle(*)(const Point_2&,  const Point_2&, const Point_2&, const Point_2&)>(&CGAL::angle));
  cgal.method("angle", static_cast<CGAL::Angle(*)(const Vector_3&, const Vector_3&)>(&CGAL::angle));
  cgal.method("angle", static_cast<CGAL::Angle(*)(const Point_3&,  const Point_3&, const Point_3&)>(&CGAL::angle));
  cgal.method("angle", static_cast<CGAL::Angle(*)(const Point_3&,  const Point_3&, const Point_3&, const Point_3&)>(&CGAL::angle));
  cgal.method("angle", static_cast<CGAL::Angle(*)(const Point_3&,  const Point_3&, const Point_3&, const Vector_3&)>(&CGAL::angle));
  cgal.unset_override_module();

  cgal.method("approximate_angle", static_cast<FT(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::approximate_angle));
  cgal.method("approximate_angle", static_cast<FT(*)(const Vector_3&, const Vector_3&)>(&CGAL::approximate_angle));

  cgal.method("approximate_dihedral_angle", static_cast<FT(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::approximate_dihedral_angle));

  cgal.method("area", static_cast<FT(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::area));

  cgal.method("are_ordered_along_line", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::are_ordered_along_line));
  cgal.method("are_ordered_along_line", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::are_ordered_along_line));

  cgal.method("are_strictly_ordered_along_line", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::are_strictly_ordered_along_line));
  cgal.method("are_strictly_ordered_along_line", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::are_strictly_ordered_along_line));

  cgal.method("barycenter", static_cast<Point_2(*)(const Point_2&, const FT&, const Point_2&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_2(*)(const Point_2&, const FT&, const Point_2&, const FT&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_2(*)(const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_2(*)(const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_2(*)(const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_2(*)(const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_3(*)(const Point_3&, const FT&, const Point_3&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_3(*)(const Point_3&, const FT&, const Point_3&, const FT&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_3(*)(const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_3(*)(const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&, const FT&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_3(*)(const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&)>(&CGAL::barycenter));
  cgal.method("barycenter", static_cast<Point_3(*)(const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&, const FT&, const Point_3&, const FT&)>(&CGAL::barycenter));

  cgal.method("bisector", static_cast<Line_2(*)(const Point_2&, const Point_2&)>(&CGAL::bisector));
  cgal.method("bisector", static_cast<Line_2(*)(const Line_2&,  const Line_2&)>(&CGAL::bisector));
  cgal.method("bisector", static_cast<Plane_3(*)(const Point_3&, const Point_3&)>(&CGAL::bisector));
  cgal.method("bisector", static_cast<Plane_3(*)(const Plane_3&,  const Plane_3&)>(&CGAL::bisector));

  cgal.method("centroid", static_cast<Point_2(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::centroid));
  cgal.method("centroid", static_cast<Point_2(*)(const Point_2&, const Point_2&, const Point_2&, const Point_2&)>(&CGAL::centroid));
  cgal.method("centroid", static_cast<Point_2(*)(const Triangle_2&)>(&CGAL::centroid));
  cgal.method("centroid", static_cast<Point_3(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::centroid));
  cgal.method("centroid", static_cast<Point_3(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::centroid));
  cgal.method("centroid", static_cast<Point_3(*)(const Triangle_3&)>(&CGAL::centroid));
  cgal.method("centroid", static_cast<Point_3(*)(const Tetrahedron_3&)>(&CGAL::centroid));

  cgal.method("circumcenter", static_cast<Point_2(*)(const Point_2&, const Point_2&)>(&CGAL::circumcenter));
  cgal.method("circumcenter", static_cast<Point_2(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::circumcenter));
  cgal.method("circumcenter", static_cast<Point_2(*)(const Triangle_2&)>(&CGAL::circumcenter));
  cgal.method("circumcenter", static_cast<Point_3(*)(const Point_3&, const Point_3&)>(&CGAL::circumcenter));
  cgal.method("circumcenter", static_cast<Point_3(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::circumcenter));
  cgal.method("circumcenter", static_cast<Point_3(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::circumcenter));
  cgal.method("circumcenter", static_cast<Point_3(*)(const Triangle_3&)>(&CGAL::circumcenter));
  cgal.method("circumcenter", static_cast<Point_3(*)(const Tetrahedron_3&)>(&CGAL::circumcenter));

  cgal.method("collinear_are_ordered_along_line", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::collinear_are_ordered_along_line));
  cgal.method("collinear_are_ordered_along_line", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::collinear_are_ordered_along_line));

  cgal.method("collinear_are_strictly_ordered_along_line", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::collinear_are_strictly_ordered_along_line));
  cgal.method("collinear_are_strictly_ordered_along_line", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::collinear_are_strictly_ordered_along_line));

  cgal.method("collinear", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::collinear));
  cgal.method("collinear", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::collinear));

  cgal.method("compare_dihedral_angle", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&, const FT&)>(&CGAL::compare_dihedral_angle));
  cgal.method("compare_dihedral_angle", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::compare_dihedral_angle));
  cgal.method("compare_dihedral_angle", static_cast<CGAL::Comparison_result(*)(const Vector_3&, const Vector_3&, const Vector_3&, const FT&)>(&CGAL::compare_dihedral_angle));
  cgal.method("compare_dihedral_angle", static_cast<CGAL::Comparison_result(*)(const Vector_3&, const Vector_3&, const Vector_3&, const Vector_3&, const Vector_3&, const Vector_3&)>(&CGAL::compare_dihedral_angle));

  cgal.method("compare_distance_to_point", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::compare_distance_to_point));
  cgal.method("compare_distance_to_point", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::compare_distance_to_point));

  cgal.method("compare_lexicographically", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Point_2&)>(&CGAL::compare_lexicographically));
  cgal.method("compare_lexicographically", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&)>(&CGAL::compare_lexicographically));

  cgal.method("compare_signed_distance_to_line", static_cast<CGAL::Comparison_result(*)(const Line_2&,  const Point_2&, const Point_2&)>(&CGAL::compare_signed_distance_to_line));
  cgal.method("compare_signed_distance_to_line", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Point_2&, const Point_2&, const Point_2&)>(&CGAL::compare_signed_distance_to_line));

  cgal.method("compare_signed_distance_to_plane", static_cast<CGAL::Comparison_result(*)(const Plane_3&,  const Point_3&, const Point_3&)>(&CGAL::compare_signed_distance_to_plane));
  cgal.method("compare_signed_distance_to_plane", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::compare_signed_distance_to_plane));

  cgal.method("compare_slope", static_cast<CGAL::Comparison_result(*)(const Line_2&,    const Line_2&)>(&CGAL::compare_slope));
  cgal.method("compare_slope", static_cast<CGAL::Comparison_result(*)(const Segment_2&, const Segment_2&)>(&CGAL::compare_slope));
  cgal.method("compare_slope", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::compare_slope));

  cgal.method("compare_squared_distance", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Point_2&, const FT&)>(&CGAL::compare_squared_distance));
  cgal.method("compare_squared_distance", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&, const FT&)>(&CGAL::compare_squared_distance));

  cgal.method("compare_squared_radius", static_cast<CGAL::Comparison_result(*)(const Point_3&, const FT&)>(&CGAL::compare_squared_radius));
  cgal.method("compare_squared_radius", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&, const FT&)>(&CGAL::compare_squared_radius));
  cgal.method("compare_squared_radius", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&, const Point_3&, const FT&)>(&CGAL::compare_squared_radius));
  cgal.method("compare_squared_radius", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&, const FT&)>(&CGAL::compare_squared_radius));

  cgal.method("compare_x", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Point_2&)>(&CGAL::compare_x));
  cgal.method("compare_x", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&)>(&CGAL::compare_x));
  cgal.method("compare_x", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Line_2&, const Line_2&)>(&CGAL::compare_x));
  cgal.method("compare_x", static_cast<CGAL::Comparison_result(*)(const Line_2&,  const Line_2&, const Line_2&)>(&CGAL::compare_x));
  cgal.method("compare_x", static_cast<CGAL::Comparison_result(*)(const Line_2&,  const Line_2&, const Line_2&, const Line_2&)>(&CGAL::compare_x));

  cgal.method("compare_xy", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Point_2&)>(&CGAL::compare_xy));

  cgal.method("compare_x_at_y", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Line_2&)>(&CGAL::compare_x_at_y));
  cgal.method("compare_x_at_y", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Line_2&, const Line_2&)>(&CGAL::compare_x_at_y));
  cgal.method("compare_x_at_y", static_cast<CGAL::Comparison_result(*)(const Line_2&,  const Line_2&, const Line_2&)>(&CGAL::compare_x_at_y));
  cgal.method("compare_x_at_y", static_cast<CGAL::Comparison_result(*)(const Line_2&,  const Line_2&, const Line_2&, const Line_2&)>(&CGAL::compare_x_at_y));

  cgal.method("compare_y_at_x", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Line_2&)>(&CGAL::compare_y_at_x));
  cgal.method("compare_y_at_x", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Line_2&, const Line_2&)>(&CGAL::compare_y_at_x));
  cgal.method("compare_y_at_x", static_cast<CGAL::Comparison_result(*)(const Line_2&,  const Line_2&, const Line_2&)>(&CGAL::compare_y_at_x));
  cgal.method("compare_y_at_x", static_cast<CGAL::Comparison_result(*)(const Line_2&,  const Line_2&, const Line_2&, const Line_2&)>(&CGAL::compare_y_at_x));
  cgal.method("compare_y_at_x", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Segment_2&)>(&CGAL::compare_y_at_x));
  cgal.method("compare_y_at_x", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Segment_2&, const Segment_2&)>(&CGAL::compare_y_at_x));

  cgal.method("compare_y", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Point_2&)>(&CGAL::compare_y));
  cgal.method("compare_y", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&)>(&CGAL::compare_y));
  cgal.method("compare_y", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Line_2&, const Line_2&)>(&CGAL::compare_y));
  cgal.method("compare_y", static_cast<CGAL::Comparison_result(*)(const Line_2&,  const Line_2&, const Line_2&)>(&CGAL::compare_y));
  cgal.method("compare_y", static_cast<CGAL::Comparison_result(*)(const Line_2&,  const Line_2&, const Line_2&, const Line_2&)>(&CGAL::compare_y));

  cgal.method("compare_xyz", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&)>(&CGAL::compare_xyz));

  cgal.method("compare_z", static_cast<CGAL::Comparison_result(*)(const Point_3&, const Point_3&)>(&CGAL::compare_z));

  cgal.method("compare_yx", static_cast<CGAL::Comparison_result(*)(const Point_2&, const Point_2&)>(&CGAL::compare_yx));

  cgal.method("coplanar", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::coplanar));

  cgal.method("coplanar_orientation", static_cast<CGAL::Orientation(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::coplanar_orientation));
  cgal.method("coplanar_orientation", static_cast<CGAL::Orientation(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::coplanar_orientation));

  cgal.method("coplanar_side_of_bounded_circle", static_cast<CGAL::Bounded_side(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::coplanar_side_of_bounded_circle));

  cgal.method("cross_product", static_cast<Vector_3(*)(const Vector_3&, const Vector_3&)>(&CGAL::cross_product));

  cgal.method("determinant", static_cast<FT(*)(const Vector_2&, const Vector_2&)>(&CGAL::determinant));
  cgal.method("determinant", static_cast<FT(*)(const Vector_3&, const Vector_3&, const Vector_3&)>(&CGAL::determinant));

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

  cgal.method("has_larger_distance_to_point", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::has_larger_distance_to_point));
  cgal.method("has_larger_distance_to_point", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::has_larger_distance_to_point));

  cgal.method("has_larger_signed_distance_to_line", static_cast<bool(*)(const Line_2&,  const Point_2&, const Point_2&)>(&CGAL::has_larger_signed_distance_to_line));
  cgal.method("has_larger_signed_distance_to_line", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&, const Point_2&)>(&CGAL::has_larger_signed_distance_to_line));

  cgal.method("has_larger_signed_distance_to_plane", static_cast<bool(*)(const Plane_3&,  const Point_3&, const Point_3&)>(&CGAL::has_larger_signed_distance_to_plane));
  cgal.method("has_larger_signed_distance_to_plane", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::has_larger_signed_distance_to_plane));

  cgal.method("has_smaller_distance_to_point", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::has_smaller_distance_to_point));
  cgal.method("has_smaller_distance_to_point", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::has_smaller_distance_to_point));

  cgal.method("has_smaller_signed_distance_to_line", static_cast<bool(*)(const Line_2&,  const Point_2&, const Point_2&)>(&CGAL::has_smaller_signed_distance_to_line));
  cgal.method("has_smaller_signed_distance_to_line", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&, const Point_2&)>(&CGAL::has_smaller_signed_distance_to_line));

  cgal.method("has_smaller_signed_distance_to_plane", static_cast<bool(*)(const Plane_3&,  const Point_3&, const Point_3&)>(&CGAL::has_smaller_signed_distance_to_plane));
  cgal.method("has_smaller_signed_distance_to_plane", static_cast<bool(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::has_smaller_signed_distance_to_plane));

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

  cgal.method("l_infinity_distance", static_cast<FT(*)(const Point_2&, const Point_2&)>(&CGAL::l_infinity_distance));
  cgal.method("l_infinity_distance", static_cast<FT(*)(const Point_3&, const Point_3&)>(&CGAL::l_infinity_distance));

  cgal.method("left_turn", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::left_turn));

  cgal.method("lexicographically_xy_larger", static_cast<bool(*)(const Point_2&, const Point_2&)>(&CGAL::lexicographically_xy_larger));

  cgal.method("lexicographically_xy_larger_or_equal", static_cast<bool(*)(const Point_2&, const Point_2&)>(&CGAL::lexicographically_xy_larger_or_equal));

  cgal.method("lexicographically_xy_smaller", static_cast<bool(*)(const Point_2&, const Point_2&)>(&CGAL::lexicographically_xy_smaller));

  cgal.method("lexicographically_xy_smaller_or_equal", static_cast<bool(*)(const Point_2&, const Point_2&)>(&CGAL::lexicographically_xy_smaller_or_equal));

  cgal.method("lexicographically_xyz_smaller", static_cast<bool(*)(const Point_3&, const Point_3&)>(&CGAL::lexicographically_xyz_smaller));

  cgal.method("lexicographically_xyz_smaller_or_equal", static_cast<bool(*)(const Point_3&, const Point_3&)>(&CGAL::lexicographically_xyz_smaller_or_equal));

  cgal.method("max_vertex", static_cast<Point_2(*)(const Iso_rectangle_2&)>(&CGAL::max_vertex));
  cgal.method("max_vertex", static_cast<Point_3(*)(const Iso_cuboid_3&)>(&CGAL::max_vertex));

  cgal.method("midpoint", static_cast<Point_2(*)(const Point_2&, const Point_2&)>(&CGAL::midpoint));
  cgal.method("midpoint", static_cast<Point_3(*)(const Point_3&, const Point_3&)>(&CGAL::midpoint));

  cgal.method("min_vertex", static_cast<Point_2(*)(const Iso_rectangle_2&)>(&CGAL::min_vertex));
  cgal.method("min_vertex", static_cast<Point_3(*)(const Iso_cuboid_3&)>(&CGAL::min_vertex));

  cgal.method("normal", static_cast<Vector_3(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::normal));

  cgal.method("orientation", static_cast<CGAL::Orientation(*)(const Point_2&,  const Point_2&, const Point_2&)>(&CGAL::orientation));
  cgal.method("orientation", static_cast<CGAL::Orientation(*)(const Vector_2&, const Vector_2&)>(&CGAL::orientation));
  cgal.method("orientation", static_cast<CGAL::Orientation(*)(const Point_3&,  const Point_3&, const Point_3&, const Point_3&)>(&CGAL::orientation));
  cgal.method("orientation", static_cast<CGAL::Orientation(*)(const Vector_3&, const Vector_3&, const Vector_3&)>(&CGAL::orientation));

  cgal.method("orthogonal_vector", static_cast<Vector_3(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::orthogonal_vector));

  cgal.method("parallel", static_cast<bool(*)(const Line_2&, const Line_2&)>(&CGAL::parallel));
  cgal.method("parallel", static_cast<bool(*)(const Ray_2&, const Ray_2&)>(&CGAL::parallel));
  cgal.method("parallel", static_cast<bool(*)(const Segment_2&, const Segment_2&)>(&CGAL::parallel));
  cgal.method("parallel", static_cast<bool(*)(const Line_3&, const Line_3&)>(&CGAL::parallel));
  cgal.method("parallel", static_cast<bool(*)(const Plane_3&, const Plane_3&)>(&CGAL::parallel));
  cgal.method("parallel", static_cast<bool(*)(const Ray_3&, const Ray_3&)>(&CGAL::parallel));
  cgal.method("parallel", static_cast<bool(*)(const Segment_3&, const Segment_3&)>(&CGAL::parallel));

  cgal.method("radical_plane", static_cast<Plane_3(*)(const Sphere_3&, const Sphere_3&)>(&CGAL::radical_plane));

  cgal.method("radical_line", static_cast<Line_2(*)(const Circle_2&, const Circle_2&)>(&CGAL::radical_line));

  cgal.method("rational_rotation_approximation", static_cast<void(*)(const RT&, const RT&, RT&, RT&, RT&, const RT&, const RT&)>(&CGAL::rational_rotation_approximation));

  cgal.method("right_turn", static_cast<bool(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::right_turn));

  cgal.method("scalar_product", static_cast<FT(*)(const Vector_2&, const Vector_2&)>(&CGAL::scalar_product));
  cgal.method("scalar_product", static_cast<FT(*)(const Vector_3&, const Vector_3&)>(&CGAL::scalar_product));

  cgal.method("side_of_bounded_circle", static_cast<CGAL::Bounded_side(*)(const Point_2&, const Point_2&, const Point_2&, const Point_2&)>(&CGAL::side_of_bounded_circle));
  cgal.method("side_of_bounded_circle", static_cast<CGAL::Bounded_side(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::side_of_bounded_circle));

  cgal.method("side_of_bounded_sphere", static_cast<CGAL::Bounded_side(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::side_of_bounded_sphere));
  cgal.method("side_of_bounded_sphere", static_cast<CGAL::Bounded_side(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::side_of_bounded_sphere));
  cgal.method("side_of_bounded_sphere", static_cast<CGAL::Bounded_side(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::side_of_bounded_sphere));

  cgal.method("side_of_oriented_circle", static_cast<CGAL::Oriented_side(*)(const Point_2&, const Point_2&, const Point_2&, const Point_2&)>(&CGAL::side_of_oriented_circle));

  cgal.method("side_of_oriented_sphere", static_cast<CGAL::Oriented_side(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::side_of_oriented_sphere));

  cgal.method("squared_area", static_cast<FT(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::squared_area));

  SQUARED_DISTANCE_2_ALL;

  SQUARED_DISTANCE_3_SYM;
  cgal.method("squared_distance", &squared_distance<Point_3, Triangle_3>);
  cgal.method("squared_distance", &squared_distance<Triangle_3, Point_3>);

  cgal.method("squared_radius", static_cast<FT(*)(const Point_2&, const Point_2&, const Point_2&)>(&CGAL::squared_radius));
  cgal.method("squared_radius", static_cast<FT(*)(const Point_2&, const Point_2&)>(&CGAL::squared_radius));
  cgal.method("squared_radius", static_cast<FT(*)(const Point_2&)>(&CGAL::squared_radius));
  cgal.method("squared_radius", static_cast<FT(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::squared_radius));
  cgal.method("squared_radius", static_cast<FT(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::squared_radius));
  cgal.method("squared_radius", static_cast<FT(*)(const Point_3&, const Point_3&)>(&CGAL::squared_radius));
  cgal.method("squared_radius", static_cast<FT(*)(const Point_3&)>(&CGAL::squared_radius));

  cgal.method("unit_normal", static_cast<Vector_3(*)(const Point_3&, const Point_3&, const Point_3&)>(&CGAL::unit_normal));

  cgal.method("volume", static_cast<FT(*)(const Point_3&, const Point_3&, const Point_3&, const Point_3&)>(&CGAL::volume));

  cgal.method("x_equal", static_cast<bool(*)(const Point_2&, const Point_2&)>(&CGAL::x_equal));
  cgal.method("x_equal", static_cast<bool(*)(const Point_3&, const Point_3&)>(&CGAL::x_equal));
  cgal.method("y_equal", static_cast<bool(*)(const Point_2&, const Point_2&)>(&CGAL::y_equal));
  cgal.method("y_equal", static_cast<bool(*)(const Point_3&, const Point_3&)>(&CGAL::y_equal));
  cgal.method("z_equal", static_cast<bool(*)(const Point_3&, const Point_3&)>(&CGAL::z_equal));

  cgal.method("do_overlap", static_cast<bool(*)(const Bbox_2&, const Bbox_2&)>(&CGAL::do_overlap));
  cgal.method("do_overlap", static_cast<bool(*)(const Bbox_3&, const Bbox_3&)>(&CGAL::do_overlap));
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
