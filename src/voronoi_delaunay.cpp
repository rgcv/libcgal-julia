#include <vector>

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
#include <CGAL/Voronoi_diagram_2.h>

#include <jlcxx/const_array.hpp>
#include <jlcxx/module.hpp>
#include <jlcxx/type_conversion.hpp>

#include <julia.h>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

typedef Kernel K;

typedef CGAL::Triangulation_2<K> Triangulation;
typedef Triangulation::Edge      T_Edge;
typedef Triangulation::Face      T_Face;
typedef Triangulation::Vertex    T_Vertex;

typedef CGAL::Delaunay_triangulation_2<K>                                    DT;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DT>                 AT;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT> AP;
typedef CGAL::Voronoi_diagram_2<DT, AT, AP>                                  VD;

typedef VD::Face     VD_Face;
typedef VD::Halfedge VD_Halfedge;
typedef VD::Site_2   VD_Site;
typedef VD::Vertex   VD_Vertex;

template <typename T, typename Iterator>
jlcxx::Array<T> collect(Iterator begin, Iterator end) {
  jlcxx::Array<T> jlarr;
  for (auto it = begin; it != end; ) jlarr.push_back(*(it++));
  return jlarr;
}

template<typename T, typename Circulator>
jlcxx::Array<T> collect(Circulator begin) {
  Circulator cc = begin;
  jlcxx::Array<T> jlarr;
  do { jlarr.push_back(*cc); } while(++cc != begin);
  return jlarr;
}

struct Handle_visitor {
  typedef jl_value_t* result_type;

  template <typename Handle>
  result_type operator()(const Handle& h) const {
    return jlcxx::box<typename Handle::value_type>(*h);
  }
};

void wrap_voronoi_delaunay(jlcxx::Module& cgal) {
  auto tedge      = cgal.add_type<T_Edge>     ("TriangulationEdge");
  auto tface      = cgal.add_type<T_Face>     ("TriangulationFace");
  auto tvertex    = cgal.add_type<T_Vertex>   ("TriangulationVertex");

  auto vdface     = cgal.add_type<VD_Face>    ("VoronoiFace");
  auto vdhalfedge = cgal.add_type<VD_Halfedge>("VoronoiHalfedge");
  auto vdvertex   = cgal.add_type<VD_Vertex>  ("VoronoiVertex");
  auto voronoi    = cgal.add_type<VD>         ("VoronoiDiagram");

  auto delaunay   = cgal.add_type<DT>         ("DelaunayTriangulation");

  tvertex
    .METHOD(T_Vertex, degree)
    .UNAMBIG_METHOD(const Point_2&, T_Vertex, point)
    ;

  vdface
    OVERRIDE_BASE(cgal, vdface)
    .BINARY_OP_SELF(VD_Face, ==)
    .BINARY_OP_SELF(VD_Face,  <)
    UNSET_OVERRIDE(cgal, vdface)
    .method("dual", [](const VD_Face& f) { return *(f.dual()); })
    .method("halfedge", [](const VD_Face& f) { return *(f.halfedge()); })
    .method("is_halfedge_on_ccb", [](const VD_Face& f, const VD_Halfedge& hf) {
      return f.is_halfedge_on_ccb(VD::Halfedge_handle(hf));
    })
    .METHOD(VD_Face, is_unbounded)
    .METHOD(VD_Face, is_valid)
    ;

  vdvertex
    OVERRIDE_BASE(cgal, vdvertex)
    .BINARY_OP_SELF(VD_Vertex, ==)
    .BINARY_OP_SELF(VD_Vertex,  <)
    UNSET_OVERRIDE(cgal, vdvertex)
    .METHOD(VD_Vertex, degree)
    .method("dual", [](const VD_Vertex& v) { return *(v.dual()); })
    .method("halfedge", [](const VD_Vertex& v) { return *(v.halfedge()); })
    .method("incident_halfedges", [](const VD_Vertex& v) {
      return collect<VD_Halfedge>(v.incident_halfedges());
    })
    .method("is_incident_edge", [](const VD_Vertex& v, const VD_Halfedge& hf) {
      return v.is_incident_edge(VD::Halfedge_handle(hf));
    })
    .method("is_incident_face", [](const VD_Vertex& v, const VD_Face& f) {
      return v.is_incident_face(VD::Face_handle(f));
    })
    .METHOD(VD_Vertex, is_valid)
    .METHOD(VD_Vertex, point)
    ;

  vdhalfedge
    OVERRIDE_BASE(cgal, vdhalfedge)
    .BINARY_OP_SELF(VD_Halfedge, ==)
    .BINARY_OP_SELF(VD_Halfedge,  <)
    UNSET_OVERRIDE(cgal, vdhalfedge)
    .METHOD(VD_Halfedge, has_source)
    .METHOD(VD_Halfedge, has_target)
    .METHOD(VD_Halfedge, is_bisector)
    .METHOD(VD_Halfedge, is_unbounded)
    .METHOD(VD_Halfedge, is_ray)
    .METHOD(VD_Halfedge, is_segment)
    .method("next", [](const VD_Halfedge& hf) { return *(hf.next()); })
    .method("previous", [](const VD_Halfedge& hf) { return *(hf.previous()); })
    .method("source", [](const VD_Halfedge& hf) {
      if (hf.has_source()) {
        return (jl_value_t*)jlcxx::box<VD_Vertex>(*(hf.source()));
      }
      return jl_nothing;
    })
    .method("target", [](const VD_Halfedge& hf) {
      if (hf.has_target()) {
        return (jl_value_t*)jlcxx::box<VD_Vertex>(*(hf.target()));
      }
      return jl_nothing;
    })
    ;

  voronoi
    OVERRIDE_BASE(cgal, voronoi)
    .method("empty!", &VD::clear)
    .method("insert!", [](VD& vd, jlcxx::ArrayRef<Point_2> ps) {
      vd.insert(ps.begin(), ps.end());
      return vd;
    })
    .method("push!", [](VD& vd, const Point_2& p) {
      vd.insert(p);
      return vd;
    })
    UNSET_OVERRIDE(cgal, voronoi)
    .method("dual", [](const VD& vd) { return vd.dual(); })
    .METHOD(VD, is_valid)
    .METHOD(VD, number_of_faces)
    .METHOD(VD, number_of_halfedges)
    .METHOD(VD, number_of_vertices)
    .method("edges", [](const VD& vd) {
      return collect<VD_Halfedge>(vd.edges_begin(), vd.edges_end());
    })
    .method("finite_edges", [](const VD& vd) {
      jl_array_t* ja = jl_alloc_array_1d(jl_array_any_type, 0);
      JL_GC_PUSH1(&ja);

      auto&& dt = vd.dual();
      for (auto eit = dt.finite_edges_begin(); eit != dt.finite_edges_end();) {
        CGAL::Object o = dt.dual(*(eit++));
        if (const Line_2* l = CGAL::object_cast<Line_2>(&o)) {
          jl_array_ptr_1d_push(ja, jlcxx::box<Line_2>(*l));
        } else if (const Ray_2* r = CGAL::object_cast<Ray_2>(&o)) {
          jl_array_ptr_1d_push(ja, jlcxx::box<Ray_2>(*r));
        } else if (const Segment_2* s = CGAL::object_cast<Segment_2>(&o)) {
          jl_array_ptr_1d_push(ja, jlcxx::box<Segment_2>(*s));
        }
      }

      JL_GC_POP();
      return (jl_value_t*)ja;
    })
    .method("locate", [](const VD& vd, const Point_2& p) {
      return boost::apply_visitor(Handle_visitor(), vd.locate(p));
    })
    .method("sites", [](const VD& vd) {
      return collect<VD_Site>(vd.sites_begin(), vd.sites_end());
    })
    .method("vertices", [](const VD& vd) {
      return collect<VD_Vertex>(vd.vertices_begin(), vd.vertices_end());
    })
    ;

  delaunay
    .CTOR(const DT&)
    OVERRIDE_BASE(cgal, delaunay)
    .method("insert!", [](DT& dt, jlcxx::ArrayRef<Point_2> ps) {
      dt.insert(ps.begin(), ps.end());
      return dt;
    })
    .method("push!", [](DT& dt, const Point_2& p) {
      dt.push_back(p);
      return dt;
    })
    UNSET_OVERRIDE(cgal, delaunay)
    .method("all_edges", [](const DT& dt) {
      return collect<T_Edge>(dt.all_edges_begin(), dt.all_edges_end());
    })
    .method("edges", [](const DT& dt) {
      return collect<T_Edge>(dt.edges_begin(), dt.edges_end());
    })
    .method("finite_edges", [](const DT& dt) {
      return collect<T_Edge>(dt.finite_edges_begin(), dt.finite_edges_end());
    })
    .METHOD(DT, is_valid)
    .method("locate", [](const DT& dt, const Point_2& p) {
      auto&& fh = dt.locate(p);
      if (fh == nullptr) return jl_nothing;
      return (jl_value_t*)jlcxx::box<T_Face>(*fh);
    })
    .method("points", [](const DT& dt) {
      return collect<Point_2>(dt.points_begin(), dt.points_end());
    })
    .method("segment", [](const DT& dt, const T_Edge& e) {
      return dt.segment(e);
    })
    ;
}
