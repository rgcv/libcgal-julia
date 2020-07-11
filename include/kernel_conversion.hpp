#ifndef CGAL_JL_KERNEL_CONVERSION_HPP
#define CGAL_JL_KERNEL_CONVERSION_HPP

#include "kernel.hpp"

typedef Circular_kernel CK;
typedef Spherical_kernel SK;

// Given a circular/spherical kernel object of type T, it converts it to its
// linear kernel object counterpart or one identical to it. Think CK::Point_2 ->
// LK::Point_2 and CK::Circular_point_2 -> LK::Point_2.
// Typical usage: To_linear<CircularType>()(CircularType) -> LinearType.
//                To_linear<SphericalType>()(SphericalType) -> LinearType.
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
struct To_linear<SK::Point_3> {
  Point_3 operator()(const SK::Point_3& p) {
    Point_3 lp(p.x(), p.y(), p.z());
    return lp;
  }
};

template<>
struct To_linear<Circular_arc_point_2> {
  Point_2 operator()(const Circular_arc_point_2& p) {
    Point_2 lp(p.x(), p.y());
    return lp;
  }
};

template<>
struct To_linear<Circular_arc_point_3> {
  Point_3 operator()(const Circular_arc_point_3& p) {
    Point_3 lp(p.x(), p.y(), p.z());
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

template<>
struct To_linear<SK::Plane_3> {
  Plane_3 operator()(const SK::Plane_3& h) {
    Plane_3 lh(h.a(), h.b(), h.c(), h.d());
    return lh;
  }
};

template<>
struct To_linear<SK::Circle_3> {
  Circle_3 operator()(const SK::Circle_3& c) {
    To_linear<SK::Point_3> p2l;
    To_linear<SK::Plane_3> h2l;
    Circle_3 lc(p2l(c.center()), c.squared_radius(), h2l(c.supporting_plane()));
    return lc;
  }
};

template<>
struct To_linear<SK::Sphere_3> {
  Sphere_3 operator()(const SK::Sphere_3& s) {
    To_linear<SK::Point_3> p2l;
    Sphere_3 ls(p2l(s.center()), s.squared_radius(), s.orientation());
    return ls;
  }
};


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


// Given a spherical kernel object of type T, it converts a linear kernel object
// to its spherical kernel counterpart or one identical to it. Think LK::Point_3
// -> SK::Point_3 and LK::Point_3 -> SK::Circular_arc_point_3.
// Typical usage: To_circular<SphericalType>()(LinearType) -> SphericalType.
// Default is just the identity operation.
template<typename T>
struct To_spherical {
  T operator()(const T& t) {
    return t;
  }
};

template<>
struct To_spherical<SK::Point_3> {
  SK::Point_3 operator()(const Point_3& p) {
    SK::Point_3 sp(p.x(), p.y(), p.z());
    return sp;
  }
};

template<>
struct To_spherical<Circular_arc_point_3> {
  Circular_arc_point_3 operator()(const Point_3& p) {
    Circular_arc_point_3 sp(To_spherical<SK::Point_3>()(p));
    return sp;
  }
};

template<>
struct To_spherical<SK::Plane_3> {
  SK::Plane_3 operator()(const Plane_3& h) {
    SK::Plane_3 sh(h.a(), h.b(), h.c(), h.d());
    return sh;
  }
};

template<>
struct To_spherical<SK::Circle_3> {
  SK::Circle_3 operator()(const Circle_3& c) {
    To_spherical<SK::Point_3> p2s;
    To_spherical<SK::Plane_3> h2s;
    SK::Circle_3 sc(p2s(c.center()), c.squared_radius(), h2s(c.supporting_plane()));
    return sc;
  }
};

template<>
struct To_spherical<SK::Line_3> {
  SK::Line_3 operator()(const Line_3& l) {
    To_spherical<SK::Point_3> p2s;
    SK::Line_3 sl(p2s(l.point(0)), p2s(l.point(1)));
    return sl;
  }
};

template<>
struct To_spherical<SK::Segment_3> {
  SK::Segment_3 operator()(const Segment_3& s) {
    To_spherical<SK::Point_3> p2s;
    SK::Segment_3 ss(p2s(s.source()), p2s(s.target()));
    return ss;
  }
};

template<>
struct To_spherical<SK::Sphere_3> {
  SK::Sphere_3 operator()(const Sphere_3& s) {
    To_spherical<SK::Point_3> p2s;
    SK::Sphere_3 ss(p2s(s.center()), s.squared_radius(), s.orientation());
    return ss;
  }
};

template<>
struct To_spherical<Line_arc_3> {
  Line_arc_3 operator()(const Segment_3& s) {
    Line_arc_3 sa(To_spherical<SK::Segment_3>()(s));
    return sa;
  }
};

#endif // CGAL_JL_KERNEL_CONVERSION_HPP
