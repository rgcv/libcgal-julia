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
    .UNAMBIG_METHOD(const Point_2&, T_Vertex, point)
    .REPR(T_Vertex)
    ;

  vdface
    OVERRIDE_BASE(cgal, vdface)
    .BINARY_OP_SELF(VD_Face, ==)
    .BINARY_OP_SELF(VD_Face,  <)
    UNSET_OVERRIDE(cgal, vdface)
    .method("dual", [](const VD_Face& f) { return *(f.dual()); })
    .method("halfedge", [](const VD_Face& f) { return *(f.halfedge()); })
    .METHOD(VD_Face, is_unbounded)
    ;

  vdvertex
    OVERRIDE_BASE(cgal, vdvertex)
    .BINARY_OP_SELF(VD_Vertex, ==)
    .BINARY_OP_SELF(VD_Vertex,  <)
    UNSET_OVERRIDE(cgal, vdvertex)
    .method("dual", [](const VD_Vertex& v) { return *(v.dual()); })
    .method("halfedge", [](const VD_Vertex& v) { return *(v.halfedge()); })
    .METHOD(VD_Vertex, is_valid)
    .METHOD(VD_Vertex, point)
    ;

  vdhalfedge
    .METHOD(VD_Halfedge, has_source)
    .METHOD(VD_Halfedge, has_target)
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
    .method("next", [](const VD_Halfedge& hf) { return *(hf.next()); })
    ;

  voronoi
    OVERRIDE_BASE(cgal, voronoi)
    .method("push!", [](VD& vd, const Point_2& p) -> VD& {
      vd.insert(p);
      return vd;
    })
    .method("empty!", &VD::clear)
    UNSET_OVERRIDE(cgal, voronoi)
    .METHOD(VD, is_valid)
    .METHOD(VD, number_of_faces)
    .METHOD(VD, number_of_halfedges)
    .METHOD(VD, number_of_vertices)
    .method("sites", [](const VD& vd) {
      return collect<VD_Site>(vd.sites_begin(), vd.sites_end());
    })
    .method("vertices", [](const VD& vd) {
      return collect<VD_Vertex>(vd.vertices_begin(), vd.vertices_end());
    })
    .method("finite_edges", [](const VD& vd) {
      jl_array_t* ja = jl_alloc_array_1d(jl_array_any_type, 0);
      JL_GC_PUSH1(&ja);

      auto& d = vd.dual();
      for (auto eit = d.finite_edges_begin(); eit != d.finite_edges_end();) {
        CGAL::Object o = d.dual(*(eit++));
        if (const Line_2 * l = CGAL::object_cast<Line_2>(&o)) {
          jl_array_ptr_1d_push(ja, jlcxx::box<Line_2>(*l));
        } else if (const Ray_2 * r = CGAL::object_cast<Ray_2>(&o)) {
          jl_array_ptr_1d_push(ja, jlcxx::box<Ray_2>(*r));
        } else if (const Segment_2 * s = CGAL::object_cast<Segment_2>(&o)) {
          jl_array_ptr_1d_push(ja, jlcxx::box<Segment_2>(*s));
        }
      }

      JL_GC_POP();
      return (jl_value_t*)ja;
    })
    .REPR(VD)
    ;

  delaunay
    .CTOR(const DT&)
    OVERRIDE_BASE(cgal, delaunay)
    .method("insert!", [](DT& dt, jlcxx::ArrayRef<Point_2> ps) -> DT& {
      dt.insert(ps.begin(), ps.end());
      return dt;
    })
    .method("push!", [](DT& dt, const Point_2& p) -> DT& { dt.push_back(p); return dt; })
    UNSET_OVERRIDE(cgal, delaunay)
    .METHOD(DT, is_valid)
    .method("edges", [](const DT& dt) {
      return collect<T_Edge>(dt.edges_begin(), dt.edges_end());
    })
    ;
}
