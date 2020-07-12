#include <CGAL/Circular_kernel_intersections.h>

#include <jlcxx/module.hpp>
#include <jlcxx/type_conversion.hpp>

#include "kernel.hpp"
#include "kernel_conversion.hpp"
#include "global_kernel_functions.hpp"
#include "macros.hpp"

#define CK_DO_INTERSECT_CONVERT(T1, T2, C1, C2) \
  cgal.PFUNC(, do_intersect, ck_do_intersect, T1, T2, C1, C2); \
  cgal.PFUNC(, do_intersect, ck_do_intersect, T2, T1, C2, C1)
#define CK_DO_INTERSECT(T1, T2) CK_DO_INTERSECT_CONVERT(T1, T2, CK::T1, CK::T2)
#define CK_DO_INTERSECT_SELF(T) \
  cgal.PFUNC(, do_intersect, ck_do_intersect, T, T, CK::T, CK::T)

#define CK_INTERSECTION_CONVERT(T1, T2, C1, C2) \
  cgal.PFUNC(, intersection, ck_intersection, T1, T2, C1, C2); \
  cgal.PFUNC(, intersection, ck_intersection, T2, T1, C2, C1)
#define CK_INTERSECTION(T1, T2) CK_INTERSECTION_CONVERT(T1, T2, CK::T1, CK::T2)
#define CK_INTERSECTION_SELF(T) \
  cgal.PFUNC(, intersection, ck_intersection, T, T, CK::T, CK::T)

template<typename T1, typename T2, typename C1, typename C2>
inline
bool
ck_do_intersect(const T1& t1, const T2& t2) {
  C1 c1 = To_circular<C1>()(t1);
  C2 c2 = To_circular<C2>()(t2);
  return CGAL::do_intersect(c1, c2);
}

template<typename T1, typename T2, typename C1, typename C2>
inline
jl_value_t*
ck_intersection(const T1& t1, const T2& t2) {
  typedef typename CGAL::CK2_Intersection_traits<CK, C1, C2>::type ResultT;

  C1 c1 = To_circular<C1>()(t1);
  C2 c2 = To_circular<C2>()(t2);
  std::vector<ResultT> res;
  CGAL::intersection(c1, c2, std::back_inserter(res));
  return boost::apply_visitor(Intersection_visitor(),
                              boost::variant<std::vector<ResultT>>(res));
}

void wrap_global_ck_functions(jlcxx::Module& cgal) {
  CK_DO_INTERSECT(Circle_2, Circular_arc_2);
  CK_DO_INTERSECT_CONVERT(Circle_2, Segment_2, CK::Circle_2, CK::Line_arc_2);
  CK_DO_INTERSECT_SELF(Circular_arc_2);
  CK_DO_INTERSECT(Circular_arc_2, Line_2);
  CK_DO_INTERSECT_CONVERT(Circular_arc_2, Segment_2, CK::Circular_arc_2, CK::Line_arc_2);

  CK_INTERSECTION_SELF(Circle_2);
  CK_INTERSECTION(Circle_2, Circular_arc_2);
  CK_INTERSECTION(Circle_2, Line_2);
  CK_INTERSECTION_CONVERT(Circle_2, Segment_2, CK::Circle_2, CK::Line_arc_2);
  CK_INTERSECTION_SELF(Circular_arc_2);
  CK_INTERSECTION(Circular_arc_2, Line_2);
  CK_INTERSECTION_CONVERT(Circular_arc_2, Segment_2, CK::Circular_arc_2, CK::Line_arc_2);
}
