#include <CGAL/Spherical_kernel_intersections.h>

#include <jlcxx/module.hpp>
#include <jlcxx/type_conversion.hpp>

#include "kernel.hpp"
#include "kernel_conversion.hpp"
#include "global_kernel_functions.hpp"
#include "macros.hpp"

#define SK_DO_INTERSECT_CONVERT(T1, T2, S1, S2) \
  cgal.method("do_intersect", &sk_do_intersect<T1, T2, S1, S2>); \
  cgal.method("do_intersect", &sk_do_intersect<T2, T1, S2, S1>)
#define SK_DO_INTERSECT(T1, T2) SK_DO_INTERSECT_CONVERT(T1, T2, SK::T1, SK::T2)
#define SK_DO_INTERSECT_3(T1, T2, T3) \
  cgal.method("do_intersect", &sk_do_intersect<T1, T2, T3, SK::T1, SK::T2, SK::T3>)
#define SK_DO_INTERSECT_SELF(T) \
  cgal.method("do_intersect", &sk_do_intersect<T, T, SK::T, SK::T>)
#define SK_DO_INTERSECT_SELF_3(T) \
  cgal.method("do_intersect", &sk_do_intersect<T, T, T, SK::T, SK::T, SK::T>)

#define SK_INTERSECTION_CONVERT(T1, T2, S1, S2) \
  cgal.method("intersection", &sk_intersection<T1, T2, S1, S2>); \
  cgal.method("intersection", &sk_intersection<T2, T1, S2, S1>)
#define SK_INTERSECTION(T1, T2) SK_INTERSECTION_CONVERT(T1, T2, SK::T1, SK::T2)
#define SK_INTERSECTION_3(T1, T2, T3) \
  cgal.method("intersection", &sk_intersection<T1, T2, T3, SK::T1, SK::T2, SK::T3>)
#define SK_INTERSECTION_SELF(T) \
  cgal.method("intersection", &sk_intersection<T, T, SK::T, SK::T>)
#define SK_INTERSECTION_SELF_3(T) \
  cgal.method("intersection", &sk_intersection<T, T, T, SK::T, SK::T, SK::T>)

namespace jlcgal {

template<typename T1, typename T2, typename S1, typename S2>
inline
bool
sk_do_intersect(const T1& t1, const T2& t2) {
  S1 s1 = To_spherical<S1>()(t1);
  S2 s2 = To_spherical<S2>()(t2);
  return CGAL::do_intersect(s1, s2);
}

template<typename T1, typename T2, typename T3,
         typename S1, typename S2, typename S3>
inline
bool
sk_do_intersect(const T1& t1, const T2& t2, const T3& t3) {
  S1 s1 = To_spherical<S1>()(t1);
  S2 s2 = To_spherical<S2>()(t2);
  S3 s3 = To_spherical<S3>()(t3);
  return CGAL::do_intersect(s1, s2, s3);
}

template<typename T1, typename T2, typename S1, typename S2>
inline
jl_value_t*
sk_intersection(const T1& t1, const T2& t2) {
  typedef typename CGAL::SK3_Intersection_traits<SK, S1, S2>::type ResultT;

  S1 s1 = To_spherical<S1>()(t1);
  S2 s2 = To_spherical<S2>()(t2);
  std::vector<ResultT> res;
  CGAL::intersection(s1, s2, std::back_inserter(res));
  return boost::apply_visitor(Intersection_visitor(),
                              boost::variant<std::vector<ResultT>>(res));
}

template<typename T1, typename T2, typename T3,
         typename S1, typename S2, typename S3>
inline
jl_value_t*
sk_intersection(const T1& t1, const T2& t2, const T3& t3) {
  typedef typename CGAL::SK3_Intersection_traits<SK, S1, S2, S3>::type ResultT;

  S1 s1 = To_spherical<S1>()(t1);
  S2 s2 = To_spherical<S2>()(t2);
  S3 s3 = To_spherical<S3>()(t3);
  std::vector<ResultT> res;
  CGAL::intersection(s1, s2, s3, std::back_inserter(res));
  return boost::apply_visitor(Intersection_visitor(),
                              boost::variant<std::vector<ResultT>>(res));
}

void wrap_global_sk_functions(jlcxx::Module& cgal) {
  SK_DO_INTERSECT_SELF(Circle_3);
  SK_DO_INTERSECT(Circle_3, Line_3);
  SK_DO_INTERSECT(Circle_3, Plane_3);
  SK_DO_INTERSECT(Circle_3, Sphere_3);
  // SK_DO_INTERSECT_CONVERT(Circle_3, Segment_3, SK::Circle_3, SK::Line_arc_3);
  // SK_DO_INTERSECT(Circle_3, Circular_arc_3);
  SK_DO_INTERSECT_SELF(Circular_arc_3);
  // SK_DO_INTERSECT(Circular_arc_3, Line_3);
  SK_DO_INTERSECT(Circular_arc_3, Plane_3);
  // SK_DO_INTERSECT(Circular_arc_3, Sphere_3);
  // SK_DO_INTERSECT_CONVERT(Circular_arc_3, Segment_3, Circular_arc_3, SK::Line_arc_3);
  SK_DO_INTERSECT_SELF_3(Sphere_3);
  SK_DO_INTERSECT_3(Sphere_3, Sphere_3, Plane_3);
  SK_DO_INTERSECT_3(Plane_3, Sphere_3, Sphere_3);
  SK_DO_INTERSECT_3(Plane_3, Plane_3, Sphere_3);
  SK_DO_INTERSECT_3(Sphere_3, Plane_3, Plane_3);

  SK_INTERSECTION_SELF(Circle_3);
  SK_INTERSECTION(Circle_3, Sphere_3);
  SK_INTERSECTION(Circle_3, Plane_3);
  SK_INTERSECTION(Circle_3, Line_3);
  // SK_INTERSECTION_CONVERT(Circle_3, Segment_3, SK::Circle_3, SK::Line_arc_3);
  // SK_INTERSECTION(Circle_3, Circular_arc_3);
  SK_INTERSECTION_SELF(Circular_arc_3);
  // SK_INTERSECTION(Circular_arc_3, Line_3);
  SK_INTERSECTION(Circular_arc_3, Plane_3);
  // SK_INTERSECTION(Circular_arc_3, Sphere_3);
  // SK_INTERSECTION_CONVERT(Circular_arc_3, Segment_3, SK::Circular_arc_3, SK::Line_arc_3);
  SK_INTERSECTION_SELF_3(Sphere_3);
  SK_INTERSECTION_3(Sphere_3, Sphere_3, Plane_3);
  SK_INTERSECTION_3(Plane_3, Sphere_3, Sphere_3);
  SK_INTERSECTION_3(Plane_3, Plane_3, Sphere_3);
  SK_INTERSECTION_3(Sphere_3, Plane_3, Plane_3);
}

} // jlcgal

#undef SK_DO_INTERSECT_CONVERT
#undef SK_DO_INTERSECT
#undef SK_DO_INTERSECT_3
#undef SK_DO_INTERSECT_SELF
#undef SK_DO_INTERSECT_SELF_3

#undef SK_INTERSECTION_CONVERT
#undef SK_INTERSECTION
#undef SK_INTERSECTION_3
#undef SK_INTERSECTION_SELF
#undef SK_INTERSECTION_SELF_3
