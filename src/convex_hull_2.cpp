#include <iterator>
#include <tuple>
#include <vector>

#include <CGAL/ch_akl_toussaint.h>
#include <CGAL/ch_bykat.h>
#include <CGAL/ch_eddy.h>
#include <CGAL/ch_graham_andrew.h>
#include <CGAL/ch_jarvis.h>
#include <CGAL/ch_melkman.h>
#include <CGAL/convex_hull_2.h>

#include <CGAL/convexity_check_2.h>

#include <CGAL/ch_selected_extreme_points_2.h>

#include <jlcxx/module.hpp>
#include <jlcxx/tuple.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "utils.hpp"

typedef typename jlcxx::ArrayRef<Point_2>::iterator InIter;
typedef typename std::back_insert_iterator<std::vector<Point_2>> OutIter;

template<OutIter (*F)(InIter, InIter, OutIter)>
jlcxx::Array<Point_2>
ch2(jlcxx::ArrayRef<Point_2> ps) {
  std::vector<Point_2> res;
  F(ps.begin(), ps.end(), std::back_inserter(res));
  return collect(res.begin(), res.end());
}

template<void (*F)(InIter, InIter, InIter&)>
inline
Point_2
ch2_ex1(jlcxx::ArrayRef<Point_2> ps) {
  jlcxx::ArrayRef<Point_2>::iterator e;
  F(ps.begin(), ps.end(), e);
  return *e;
}

template<void (*F)(InIter, InIter, InIter&, InIter&)>
inline
std::tuple<Point_2, Point_2>
ch2_ex2(jlcxx::ArrayRef<Point_2> ps) {
  jlcxx::ArrayRef<Point_2>::iterator e1, e2;
  F(ps.begin(), ps.end(), e1, e2);
  return std::make_tuple(*e1, *e2);
}

#define CH2(F) cgal.PFUNC(, F, ch2, CGAL::F)
#define CH2_EX1(D) cgal.PFUNC(, ch_##D##_point, ch2_ex1, CGAL::ch_##D##_point)
#define CH2_EX2(D) cgal.PFUNC(, ch_##D##_point, ch2_ex2, CGAL::ch_##D##_point)

void wrap_convex_hull_2(jlcxx::Module& cgal) {
  // Convex Hull Functions
  CH2(ch_akl_toussaint);
  CH2(ch_bykat);
  CH2(ch_eddy);
  CH2(ch_graham_andrew);
  CH2(ch_jarvis);
  CH2(ch_melkman);
  CH2(convex_hull_2);

  // Convexity Checking
  cgal.method("is_ccw_strongly_convex_2", [](jlcxx::ArrayRef<Point_2> ps) {
    return CGAL::is_ccw_strongly_convex_2(ps.begin(), ps.end());
  });
  cgal.method("is_cw_strongly_convex_2", [](jlcxx::ArrayRef<Point_2> ps) {
    return CGAL::is_cw_strongly_convex_2(ps.begin(), ps.end());
  });

  // Hull Subsequence Functions
  CH2(ch_graham_andrew_scan);

  cgal.method("ch_jarvis_march", [](jlcxx::ArrayRef<Point_2> ps,
                                    const Point_2& p, const Point_2& q) {
    std::vector<Point_2> res;
    CGAL::ch_jarvis_march(ps.begin(), ps.end(), p, q, std::back_inserter(res));
    return collect(res.begin(), res.end());
  });

  CH2(lower_hull_points_2);
  CH2(upper_hull_points_2);

  // Extreme Point Functions
  CH2_EX1(e);
  CH2_EX1(n);
  CH2_EX2(ns);

  cgal.method("ch_nswe_point", [](jlcxx::ArrayRef<Point_2> ps) {
    jlcxx::ArrayRef<Point_2>::iterator n, s, w, e;
    CGAL::ch_nswe_point(ps.begin(), ps.end(), n, s, w, e);
    return std::make_tuple(*n, *s, *w, *e);
  });

  CH2_EX1(s);
  CH2_EX2(we);
  CH2_EX1(w);
}

#undef CH2
#undef CH2_EX
#undef CH2_EX2
