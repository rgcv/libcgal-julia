#ifndef CGAL_JL_KERNEL_CONVERSION_HPP
#define CGAL_JL_KERNEL_CONVERSION_HPP

#include "kernel.hpp"

typedef Circular_kernel CK;

// Given a circular kernel object of type T, it converts a linear kernel object
// to its circular kernel counterpart or one identical to it. Think LK::Point_2
// -> CK::Point_2 and LK::Point_2 -> CK::Circular_arc_point_2.
// Typical usage: To_circular<CircularType>()(LinearType) -> CircularType.
// Default is just the identity operation.
template<typename T>
struct To_circular {
  T operator()(const T& t) {
    return t;
  }
};

template<>
struct To_circular<CK::Point_2> {
  CK::Point_2 operator()(const Point_2& p) {
    CK::Point_2 cp(p.x(), p.y());
    return cp;
  }
};

template<>
struct To_circular<Circular_arc_point_2> {
  Circular_arc_point_2 operator()(const Point_2& p) {
    Circular_arc_point_2 cp(To_circular<CK::Point_2>()(p));
    return cp;
  }
};

template<>
struct To_circular<CK::Circle_2> {
  CK::Circle_2 operator()(const Circle_2& c) {
    CK::Circle_2 cc(To_circular<CK::Point_2>()(c.center()), c.squared_radius());
    return cc;
  }
};

template<>
struct To_circular<CK::Line_2> {
  CK::Line_2 operator()(const Line_2& l) {
    CK::Line_2 cl(l.a(), l.b(), l.c());
    return cl;
  }
};

template<>
struct To_circular<CK::Segment_2> {
  CK::Segment_2 operator()(const Segment_2& s) {
    To_circular<CK::Point_2> p2c;
    CK::Segment_2 cs(p2c(s.source()), p2c(s.target()));
    return cs;
  }
};

template<>
struct To_circular<Line_arc_2> {
  Line_arc_2 operator()(const Segment_2& s) {
    Line_arc_2 la(To_circular<CK::Segment_2>()(s));
    return la;
  }
};

// Given a circular kernel object of type T, it converts it to its linear kernel
// object counterpart or one identical to it. Think CK::Point_2 -> LK::Point_2
// and CK::Circular_point_2 -> LK::Point_2.
// Typical usageL To_linear<CircularType>()(CircularType) -> LinearType.
// Default is just the identity operation.
template<typename T>
struct To_linear {
  T operator()(const T& t) {
    return t;
  }
};

template<>
struct To_linear<CK::Point_2> {
  Point_2 operator()(const CK::Point_2& p) {
    Point_2 lp(p.x(), p.y());
    return lp;
  }
};

template<>
struct To_linear<Circular_arc_point_2> {
  Point_2 operator()(const CK::Circular_arc_point_2& p) {
    Point_2 lp(p.x(), p.y());
    return lp;
  }
};

template<>
struct To_linear<CK::Circle_2> {
  Circle_2 operator()(const CK::Circle_2& c) {
    Circle_2 lc(To_linear<CK::Point_2>()(c.center()), c.squared_radius());
    return lc;
  }
};

#endif // CGAL_JL_KERNEL_CONVERSION_HPP
