#include <jlcxx/module.hpp>

#include "macros.hpp"

#include "kernel.hpp"

#define DO_INTERSECT(T1, T2) \
  CGAL_GLOBAL_FUNCTION(bool, do_intersect, const T1&, const T2&); \
  CGAL_GLOBAL_FUNCTION(bool, do_intersect, const T2&, const T1&)
#define DO_INTERSECT_SELF(T) \
  CGAL_GLOBAL_FUNCTION(bool, do_intersect, const T&, const T&)

#define INTERSECTION(T1, T2) \
  cgal.SPFUNC(, intersection, T1, T2); \
  cgal.SPFUNC(, intersection, T2, T1)
#define INTERSECTION_SELF(T) cgal.SPFUNC(, intersection, T, T)

#define SQUARED_DISTANCE(T) \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Point_2&); \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Line_2&); \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Ray_2&); \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Segment_2&); \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Triangle_2&)

struct Intersection_visitor {
  typedef jl_value_t* result_type;

  template<typename T>
  jl_value_t* operator()(const T& t) const {
    return jlcxx::box<T>(t);
  }

  jl_value_t* operator()(const std::vector<Point_2>& ts) const {
    jlcxx::Array<Point_2> jlarr;
    for (auto t : ts) jlarr.push_back(t);
    return (jl_value_t*)jlarr.wrapped();
  }
};

template <typename T1, typename T2>
jl_value_t* intersection(const T1& t1, const T2& t2) {
  auto result = CGAL::intersection(t1, t2);
  if (result) {
    return boost::apply_visitor(Intersection_visitor(), *result);
  }
  return jl_nothing;
}

void wrap_global_kernel_functions(jlcxx::Module& cgal) {
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Vector_2&, const Vector_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_2&,  const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(FT, area, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, are_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, are_strictly_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, barycenter, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&, const Point_2&, const FT&);

  CGAL_GLOBAL_FUNCTION(Line_2, bisector, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Line_2, bisector, const Line_2&,  const Line_2&);

  CGAL_GLOBAL_FUNCTION(Point_2, centroid, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, centroid, const Point_2&, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, centroid, const Triangle_2&);

  CGAL_GLOBAL_FUNCTION(Point_2, circumcenter, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, circumcenter, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(Point_2, circumcenter, const Triangle_2&);

  CGAL_GLOBAL_FUNCTION(bool, collinear_are_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, collinear_are_strictly_ordered_along_line, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, collinear, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_distance_to_point, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_lexicographically, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_signed_distance_to_line, const Line_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_signed_distance_to_line, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_slope, const Line_2&,    const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_slope, const Segment_2&, const Segment_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_squared_distance, const Point_2&, const Point_2&, const FT&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_x, const Point_2&, const Point_2&);
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
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Point_2&, const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Line_2&,  const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_y, const Line_2&,  const Line_2&, const Line_2&, const Line_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Comparison_result, compare_yx, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(FT, determinant, const Vector_2&, const Vector_2&);

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

  CGAL_GLOBAL_FUNCTION(bool, has_larger_distance_to_point, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, has_larger_signed_distance_to_line, const Line_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, has_larger_signed_distance_to_line, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, has_smaller_distance_to_point, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, has_smaller_signed_distance_to_line, const Line_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, has_smaller_signed_distance_to_line, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  INTERSECTION_SELF(Iso_rectangle_2);
  INTERSECTION(Iso_rectangle_2, Line_2);
  INTERSECTION(Iso_rectangle_2, Ray_2);
  INTERSECTION(Iso_rectangle_2, Segment_2);
  INTERSECTION(Iso_rectangle_2, Triangle_2);
  INTERSECTION_SELF(Line_2);
  INTERSECTION(Line_2, Ray_2);
  INTERSECTION(Line_2, Segment_2);
  INTERSECTION(Line_2, Triangle_2);
  INTERSECTION_SELF(Ray_2);
  INTERSECTION(Ray_2, Segment_2);
  INTERSECTION(Ray_2, Triangle_2);
  INTERSECTION_SELF(Segment_2);
  INTERSECTION(Segment_2, Triangle_2);
  INTERSECTION_SELF(Triangle_2);
  // TODO: Circular Intersections

  CGAL_GLOBAL_FUNCTION(FT, l_infinity_distance, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, left_turn, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xy_larger, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xy_larger_or_equal, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xy_smaller, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, lexicographically_xy_smaller_or_equal, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(Point_2, max_vertex, const Iso_rectangle_2&);

  CGAL_GLOBAL_FUNCTION(Point_2, midpoint, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(Point_2, min_vertex, const Iso_rectangle_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Orientation, orientation, const Point_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Orientation, orientation, const Vector_2&, const Vector_2&);

  CGAL_GLOBAL_FUNCTION(bool, parallel, const Line_2&, const Line_2&);
  CGAL_GLOBAL_FUNCTION(bool, parallel, const Ray_2&, const Ray_2&);
  CGAL_GLOBAL_FUNCTION(bool, parallel, const Segment_2&, const Segment_2&);

  CGAL_GLOBAL_FUNCTION(Line_2, radical_line, const Circle_2&, const Circle_2&);

  CGAL_GLOBAL_FUNCTION(void, rational_rotation_approximation, const RT&, const RT&, RT&, RT&, RT&, const RT&, const RT&);

  CGAL_GLOBAL_FUNCTION(bool, right_turn, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(FT, scalar_product, const Vector_2&, const Vector_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Bounded_side, side_of_bounded_circle, const Point_2&, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Bounded_side, side_of_bounded_circle, const Point_2&, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(CGAL::Oriented_side, side_of_oriented_circle, const Point_2&, const Point_2&, const Point_2&, const Point_2&);

  SQUARED_DISTANCE(Point_2);
  SQUARED_DISTANCE(Line_2);
  SQUARED_DISTANCE(Ray_2);
  SQUARED_DISTANCE(Segment_2);
  SQUARED_DISTANCE(Triangle_2);

  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_2&, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(FT, squared_radius, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, x_equal, const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(bool, y_equal, const Point_2&, const Point_2&);

  CGAL_GLOBAL_FUNCTION(bool, do_overlap, const Bbox_2&, const Bbox_2&);
}

#undef DO_INTERSECT
#undef DO_INTERSECT_SELF

#undef INTERSECTION
#undef INTERSECTION_SELF

#undef SQUARED_DISTANCE
