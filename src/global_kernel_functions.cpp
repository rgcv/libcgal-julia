#include <jlcxx/module.hpp>

#include "jlcxx.hpp"

#include "enum.hpp"
#include "kernel.hpp"
#include "global_kernel_functions.hpp"

#define GLOBAL_FUNCTION(R, F, ArgsT...) \
  cgal.method(#F, static_cast<R(*)(ArgsT)>(&CGAL::F))

#define DO_INTERSECT(T1, T2) \
  GLOBAL_FUNCTION(bool, do_intersect, const T1&, const T2&); \
  GLOBAL_FUNCTION(bool, do_intersect, const T2&, const T1&)
#define DO_INTERSECT_SELF(T) \
  GLOBAL_FUNCTION(bool, do_intersect, const T&, const T&)

#define SQUARED_DISTANCE(T) \
  GLOBAL_FUNCTION(FT, squared_distance, const T&, const Point_2&); \
  GLOBAL_FUNCTION(FT, squared_distance, const T&, const Line_2&); \
  GLOBAL_FUNCTION(FT, squared_distance, const T&, const Ray_2&); \
  GLOBAL_FUNCTION(FT, squared_distance, const T&, const Segment_2&); \
  GLOBAL_FUNCTION(FT, squared_distance, const T&, const Triangle_2&)

void wrap_global_kernel_functions(jlcxx::Module& cgal) {
  GLOBAL_FUNCTION(CGAL::Angle, angle, const Vector_2&, const Vector_2&);
  GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_2&,  const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_2&,  const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(FT, area, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, are_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, are_strictly_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&);
  GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&);
  GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&);
  GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&);
  GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&);
  GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&);

  GLOBAL_FUNCTION(Line_2, bisector, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(Line_2, bisector, const Line_2&,  const Line_2&);

  GLOBAL_FUNCTION(Point_2, centroid, const Point_2&, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(Point_2, centroid, const Point_2&, const Point_2&, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(Point_2, centroid, const Triangle_2&);

  GLOBAL_FUNCTION(Point_2, circumcenter, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(Point_2, circumcenter, const Point_2&, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(Point_2, circumcenter, const Triangle_2&);

  GLOBAL_FUNCTION(bool, collinear_are_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, collinear_are_strictly_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, collinear, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_distance_to_point, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_lexicographically, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_signed_distance_to_line, const Line_2&,  const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_signed_distance_to_line, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_slope, const Line_2&,    const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_slope, const Segment_2&, const Segment_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_squared_distance, const Point_2&, const Point_2&, const FT&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Point_2&, const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Line_2&,  const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Line_2&,  const Line_2&, const Line_2&, const Line_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_xy, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x_at_y, const Point_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x_at_y, const Point_2&, const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x_at_y, const Line_2&,  const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x_at_y, const Line_2&,  const Line_2&, const Line_2&, const Line_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Point_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Point_2&, const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Line_2&,  const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Line_2&,  const Line_2&, const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Point_2&, const Segment_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y_at_x, const Point_2&, const Segment_2&, const Segment_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Point_2&, const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Line_2&,  const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Line_2&,  const Line_2&, const Line_2&, const Line_2&);

  GLOBAL_FUNCTION(CGAL::Comparison_result, compare_yx, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(FT, determinant, const Vector_2&, const Vector_2&);

  DO_INTERSECT_SELF(Circle_2);
  DO_INTERSECT(Circle_2, Iso_rectangle_2);
  DO_INTERSECT(Circle_2, Line_2);
  DO_INTERSECT(Circle_2, Point_2);
  DO_INTERSECT_SELF(Iso_rectangle_2);
  DO_INTERSECT(Iso_rectangle_2, Line_2);
  DO_INTERSECT(Iso_rectangle_2, Point_2);
  DO_INTERSECT(Iso_rectangle_2, Ray_2);
  DO_INTERSECT(Iso_rectangle_2, Segment_2);
  DO_INTERSECT(Iso_rectangle_2, Triangle_2);
  DO_INTERSECT_SELF(Line_2);
  DO_INTERSECT(Line_2, Point_2);
  DO_INTERSECT(Line_2, Ray_2);
  DO_INTERSECT(Line_2, Segment_2);
  DO_INTERSECT(Line_2, Triangle_2);
  DO_INTERSECT_SELF(Point_2);
  DO_INTERSECT(Point_2, Ray_2);
  DO_INTERSECT(Point_2, Segment_2);
  DO_INTERSECT(Point_2, Triangle_2);
  DO_INTERSECT_SELF(Ray_2);
  DO_INTERSECT(Ray_2, Segment_2);
  DO_INTERSECT(Ray_2, Triangle_2);
  DO_INTERSECT_SELF(Segment_2);
  DO_INTERSECT(Segment_2, Triangle_2);
  DO_INTERSECT_SELF(Triangle_2);

  GLOBAL_FUNCTION(bool, has_larger_distance_to_point, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, has_larger_signed_distance_to_line, const Line_2&,  const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(bool, has_larger_signed_distance_to_line, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, has_smaller_distance_to_point, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, has_smaller_signed_distance_to_line, const Line_2&,  const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(bool, has_smaller_signed_distance_to_line, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  // TODO: Intersections

  GLOBAL_FUNCTION(FT, l_infinity_distance, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, left_turn, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, lexicographically_xy_larger, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, lexicographically_xy_larger_or_equal, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, lexicographically_xy_smaller, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, lexicographically_xy_smaller_or_equal, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(Point_2, max_vertex, const Iso_rectangle_2&);

  GLOBAL_FUNCTION(Point_2, midpoint, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(Point_2, min_vertex, const Iso_rectangle_2&);

  GLOBAL_FUNCTION(CGAL::Orientation, orientation, const Point_2&,  const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(CGAL::Orientation, orientation, const Vector_2&, const Vector_2&);

  GLOBAL_FUNCTION(bool, parallel, const Line_2&, const Line_2&);
  GLOBAL_FUNCTION(bool, parallel, const Ray_2&, const Ray_2&);
  GLOBAL_FUNCTION(bool, parallel, const Segment_2&, const Segment_2&);

  GLOBAL_FUNCTION(Line_2, radical_line, const Circle_2&, const Circle_2&);

  GLOBAL_FUNCTION(void, rational_rotation_approximation, const RT&, const RT&, RT&, RT&, RT&, const RT&, const RT&);

  GLOBAL_FUNCTION(bool, right_turn, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(FT, scalar_product, const Vector_2&, const Vector_2&);

  GLOBAL_FUNCTION(CGAL::Bounded_side, side_of_bounded_circle, const Point_2&, const Point_2&, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(CGAL::Bounded_side, side_of_bounded_circle, const Point_2&, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(CGAL::Oriented_side, side_of_oriented_circle, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  SQUARED_DISTANCE(Point_2);
  SQUARED_DISTANCE(Line_2);
  SQUARED_DISTANCE(Ray_2);
  SQUARED_DISTANCE(Segment_2);
  SQUARED_DISTANCE(Triangle_2);

  GLOBAL_FUNCTION(FT, squared_radius, const Point_2&, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(FT, squared_radius, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(FT, squared_radius, const Point_2&);

  GLOBAL_FUNCTION(bool, x_equal, const Point_2&, const Point_2&);
  GLOBAL_FUNCTION(bool, y_equal, const Point_2&, const Point_2&);

  GLOBAL_FUNCTION(bool, do_overlap, const Bbox_2&, const Bbox_2&);
}

#undef GLOBAL_FUNCTION
#undef DO_INTERSECT
#undef DO_INTERSECT_SELF
#undef SQUARED_DISTANCE
