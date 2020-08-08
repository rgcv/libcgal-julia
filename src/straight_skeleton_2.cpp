#include <memory>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <CGAL/Straight_skeleton_2.h>
#include <CGAL/create_offset_polygons_2.h>
#include <CGAL/create_straight_skeleton_2.h>
#include <CGAL/create_straight_skeleton_from_polygon_with_holes_2.h>

#include <jlcxx/module.hpp>
#include <jlcxx/smart_pointers.hpp>

#include <julia.h>

#include "polygon_2.hpp"
#include "utils.hpp"

namespace jlcgal {

template<typename T>
std::shared_ptr<T>
to_std(boost::shared_ptr<T> ptr) {
  return std::shared_ptr<T>(ptr.get(), [ptr](T*) mutable { ptr.reset(); });
}

template<typename Polygon>
jlcxx::Array<Polygon>
to_poly_jlarr(std::vector<boost::shared_ptr<Polygon>> ps) {
  jlcxx::Array<Polygon> jlarr;
  for (const auto& poly : ps) jlarr.push_back(Polygon(*poly));
  return jlarr;
}

void wrap_straight_skeleton_2(jlcxx::Module& cgal) {
  typedef CGAL::Straight_skeleton_2<Kernel> Skeleton_2;

  typedef CGAL::HalfedgeDS_in_place_list_face<Skeleton_2::Face>         Face;
  typedef CGAL::HalfedgeDS_in_place_list_halfedge<Skeleton_2::Halfedge> Halfedge;
  typedef CGAL::HalfedgeDS_in_place_list_vertex<Skeleton_2::Vertex>     Vertex;

  const std::string skel_2_name = "StraightSkeleton2";

  auto ssf = cgal.add_type<Face>    (skel_2_name + "Face");
  auto ssh = cgal.add_type<Halfedge>(skel_2_name + "Halfedge");
  auto ssv = cgal.add_type<Vertex>  (skel_2_name + "Vertex");

  ssf
    // Access Functions
    .method("id", &Face::id)
    .method("halfedge", [](const Face& f) { return *f.halfedge(); })
    ;

  ssh
    // Access Functions
    .method("id",       &Halfedge::id)
    .method("opposite", [](const Halfedge& h) { return *h.opposite(); })
    .method("next",     [](const Halfedge& h) { return *h.next(); })
    .method("prev",     [](const Halfedge& h) { return *h.prev(); })
    .method("vertex",   [](const Halfedge& h) { return *h.vertex(); })
    .method("face",     [](const Halfedge& h) { return *juliah.face(); })
    .method("defining_contour_edge", [](const Halfedge& h) {
      return *h.defining_contour_edge();
    })
    // Predicates
    .method("has_null_segment",  &Halfedge::has_null_segment)
    .method("has_infinite_time", &Halfedge::has_infinite_time)
    .method("is_border",         &Halfedge::is_border)
    .method("is_bisector",       &Halfedge::is_bisector)
    .method("is_inner_bisector", &Halfedge::is_inner_bisector)
    .method("slope",             &Halfedge::slope)
    ;

  ssv
    // Access Functions
    .method("id",       &Vertex::id)
    .method("degree",   &Vertex::degree)
    .method("halfedge", [](const Vertex& v) { return *v.halfedge(); })
    .method("point",    &Vertex::point)
    ;
  cgal.set_override_module(jl_base_module);
  ssv
    .method("time", &Vertex::time)
    ;
  cgal.unset_override_module();
  ssv
    .method("primary_bisector", [](const Vertex& v) {
      return *v.primary_bisector();
    })
    // Queries
    .method("has_infinite_time", &Vertex::has_infinite_time)
    .method("has_null_point",    &Vertex::has_null_point)
    .method("is_contour",        &Vertex::is_contour)
    .method("is_skeleton",       &Vertex::is_skeleton)
    .method("is_split",          &Vertex::is_split)
    ;

  cgal.add_type<Skeleton_2>(skel_2_name)
    // Access Member Functions
    .method("size_of_faces",     &Skeleton_2::size_of_faces)
    .method("size_of_halfedges", &Skeleton_2::size_of_halfedges)
    .method("size_of_vertices",  &Skeleton_2::size_of_vertices)
    .method("faces", [](const Skeleton_2& s) {
      return collect(s.faces_begin(), s.faces_end());
    })
    .method("halfedges", [](const Skeleton_2& s) {
      return collect(s.halfedges_begin(), s.halfedges_end());
    })
    .method("vertices", [](const Skeleton_2& s) {
      return collect(s.vertices_begin(), s.vertices_end());
    })
    // Predicates
    .method("is_valid", &Skeleton_2::is_valid)
    ;

  cgal.method("create_exterior_straight_skeleton_2",
              [](const FT& max_offset, const Polygon_2& poly) {
    return to_std(CGAL::create_exterior_straight_skeleton_2(max_offset,
                                                            poly,
                                                            Kernel()));
  });
  cgal.method("create_exterior_straight_skeleton_2",
              [](const FT& max_offset, jlcxx::ArrayRef<Point_2> ps) {
    // because `bbox_2` uses operator-> from the input iterator... which
    // ArrayRef::iterator is missing, so we copy it into a vector.
    std::vector<Point_2> vps(ps.begin(), ps.end());
    return to_std(CGAL::create_exterior_straight_skeleton_2(max_offset,
                                                            vps.begin(),
                                                            vps.end(),
                                                            Kernel()));
  });
  cgal.method("create_interior_straight_skeleton_2", [](const Polygon_2& poly) {
    return to_std(CGAL::create_interior_straight_skeleton_2(poly, Kernel()));
  });
  cgal.method("create_interior_straight_skeleton_2",
              [](const Polygon_with_holes_2& poly) {
    return to_std(CGAL::create_interior_straight_skeleton_2(poly));
  });
  cgal.method("create_interior_straight_skeleton_2",
              [](jlcxx::ArrayRef<Point_2> contour) {
    return to_std(CGAL::create_interior_straight_skeleton_2(contour.begin(),
                                                            contour.end(),
                                                            Kernel()));
  });
  cgal.method("create_interior_straight_skeleton_2",
              [](jlcxx::ArrayRef<Point_2> contour,
                 jlcxx::ArrayRef<Polygon_2> holes) {
    return to_std(CGAL::create_interior_straight_skeleton_2(contour.begin(),
                                                            contour.end(),
                                                            holes.begin(),
                                                            holes.end(),
                                                            Kernel()));
  });

  cgal.method("create_offset_polygons_2", [](const FT& offset,
                                             const Skeleton_2& ss) {
    return to_poly_jlarr(CGAL::create_offset_polygons_2(offset, ss, Kernel()));
  });
}

} // jlcgal
