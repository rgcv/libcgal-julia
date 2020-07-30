#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

#include <CGAL/Dimension.h>
#include <CGAL/Kernel/Dimension_utils.h>
#include <CGAL/barycenter.h>
#include <CGAL/bounding_box.h>
#include <CGAL/centroid.h>

#include <jlcxx/module.hpp>
#include <jlcxx/tuple.hpp>

#include "kernel.hpp"
namespace jlcgal {

template<typename Point>
Point
barycenter(jlcxx::ArrayRef<Point> ps, jlcxx::ArrayRef<FT> ws) {
  if (ps.size() != ws.size()) {
    throw std::invalid_argument("#points != #weights");
  }

  std::vector<std::pair<Point, FT>> v(ps.size());
  for (std::size_t i = 0; i < ps.size(); ++i) {
    v[i] = std::make_pair(ps[i], ws[i]);
  }

  return CGAL::barycenter(v.begin(), v.end());
}

template<typename WeightedPoint, int>
typename WeightedPoint::Point
barycenter(jlcxx::ArrayRef<WeightedPoint> wps) {
  std::vector<std::pair<typename WeightedPoint::Point, FT>> v(wps.size());
  std::transform(wps.begin(), wps.end(), v.begin(),
                 [](const WeightedPoint& wp) {
    return std::make_pair(wp.point(), wp.weight());
  });
  return CGAL::barycenter(v.begin(), v.end());
}

template<typename Point>
typename CGAL::Access::Iso_box<Kernel, typename
                               CGAL::Ambient_dimension<Point, Kernel>::type>::type
bounding_box(jlcxx::ArrayRef<Point> ps) {
  return CGAL::bounding_box(ps.begin(), ps.end());
}

template<typename T>
typename CGAL::Access::Point<Kernel, typename
                             CGAL::Ambient_dimension<T, Kernel>::type>::type
centroid(jlcxx::ArrayRef<T> ts) {
  /* return CGAL::centroid(ts.begin(), ts.end()); */
  // HACK: see https://github.com/JuliaInterop/libcxxwrap-julia/issues/58
  std::vector<T> v(ts.begin(), ts.end());
  return CGAL::centroid(v.begin(), v.end());
}

void wrap_principal_component_analysis(jlcxx::Module& cgal) {
  // barycenter
  cgal.method("barycenter", &barycenter<Point_2>);
  cgal.method("barycenter", &barycenter<Point_3>);
  cgal.method("barycenter", &barycenter<Weighted_point_2, 0>);
  cgal.method("barycenter", &barycenter<Weighted_point_3, 0>);
  // bounding_box
  cgal.method("bounding_box", &bounding_box<Point_2>);
  cgal.method("bounding_box", &bounding_box<Point_3>);
  // centroid
  cgal.method("centroid", &centroid<Point_2>);
  cgal.method("centroid", &centroid<Point_3>);
#ifndef JLCGAL_EXACT_CONSTRUCTIONS
  cgal.method("centroid", &centroid<Segment_2>);
  cgal.method("centroid", &centroid<Segment_3>);
  cgal.method("centroid", &centroid<Triangle_2>);
  cgal.method("centroid", &centroid<Triangle_3>);
  cgal.method("centroid", &centroid<Iso_rectangle_2>);
  cgal.method("centroid", &centroid<Iso_cuboid_3>);
  cgal.method("centroid", &centroid<Tetrahedron_3>);
  cgal.method("centroid", &centroid<Circle_2>);
  cgal.method("centroid", &centroid<Sphere_3>);
#endif
}

} // jlcgal
