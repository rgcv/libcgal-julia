#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <boost/variant/apply_visitor.hpp>

#include <CGAL/Circular_kernel_2/Intersection_traits.h>

#include <jlcxx/module.hpp>
#include <jlcxx/type_conversion.hpp>

#include <julia.h>

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

#define CK_INTERSECTION(T1, T2) \
  cgal.PFUNC(, intersection, ck_intersection, T1, T2); \
  cgal.PFUNC(, intersection, ck_intersection, T2, T1);
#define CK_INTERSECTION_SELF(T) \
  cgal.PFUNC(, intersection, ck_intersection, T, T)

#define SQUARED_DISTANCE(T) \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Point_2&); \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Line_2&); \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Ray_2&); \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Segment_2&); \
  CGAL_GLOBAL_FUNCTION(FT, squared_distance, const T&, const Triangle_2&)

typedef Kernel K;
typedef Circular_kernel CK;

typedef Kernel::FT FT;
typedef Kernel::RT RT;

struct Intersection_visitor {
  typedef jl_value_t* result_type;

  jl_value_t* operator()(const std::pair<K::Circular_arc_point_2, unsigned>& p) const {
    return jlcxx::create<Point_2>(p.first.x(), p.first.y());
  }

  template<typename T>
  jl_value_t* operator()(const T& t) const { return jlcxx::box<T>(t); }

  template<typename... TS>
  jl_value_t* operator()(const boost::variant<TS...>& v) const {
    return boost::apply_visitor(*this, v);
  }

  template<typename T>
  jl_value_t* operator()(const std::vector<T>& ts) const {
    if (ts.empty()) return jl_nothing;

    auto first = (*this)(ts[0]);
    if (ts.size() == 1) return first;

    jl_value_t* atype = jl_apply_array_type(jl_typeof(first), 1);
    jl_array_t* ja = jl_alloc_array_1d(atype, ts.size());
    JL_GC_PUSH1(&ja);
    for (size_t i = 0; i < ts.size(); ++i) {
      jl_arrayset(ja, (*this)(ts[i]), i);
    }
    JL_GC_POP();

    return (jl_value_t*)ja;
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

template <typename T1, typename T2>
jl_value_t* ck_intersection(const T1& t1, const T2& t2) {
  std::vector<typename CGAL::CK2_Intersection_traits<K, T1, T2>::type> results;
  CGAL::intersection(t1, t2, std::back_inserter(results));
  auto v = boost::variant<decltype(results)>(results);
  return boost::apply_visitor(Intersection_visitor(), v);
}

void wrap_global_kernel_functions(jlcxx::Module& cgal) {
  OVERRIDE_BASE(cgal,);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Vector_2&, const Vector_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_2&,  const Point_2&, const Point_2&);
  CGAL_GLOBAL_FUNCTION(CGAL::Angle, angle, const Point_2&,  const Point_2&, const Point_2&, const Point_2&);
  UNSET_OVERRIDE(cgal,);

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
  // TODO: Other circular Intersections
  CK_INTERSECTION_SELF(Circle_2);

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
