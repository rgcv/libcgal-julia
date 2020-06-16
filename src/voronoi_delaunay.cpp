#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
#include <CGAL/Voronoi_diagram_2.h>

#include <jlcxx/module.hpp>

#include <julia.h>

#include "macros.hpp"
#include "triangulation.hpp"
#include "utils.hpp"

using DG = DTr;
using AT = CGAL::Delaunay_triangulation_adaptation_traits_2<DG>;
using AP = CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DG>;
using VD = CGAL::Voronoi_diagram_2<DG, AT, AP>;

void wrap_voronoi_delaunay(jlcxx::Module& cgal) {
  const std::string vd_name = "VoronoiDiagram2";
  auto vd         = cgal.add_type<VD>          (vd_name);
  auto vdface     = cgal.add_type<VD::Face>    (vd_name + "Face");
  auto vdhalfedge = cgal.add_type<VD::Halfedge>(vd_name + "Halfedge");
  auto vdvertex   = cgal.add_type<VD::Vertex>  (vd_name + "Vertex");

  vdface
    .CTOR(const VD::Face&)
    OVERRIDE_BASE(cgal, vdface)
    .BINARY_OP_SELF(VD::Face, ==)
    .BINARY_OP_SELF(VD::Face,  <)
    UNSET_OVERRIDE(cgal, vdface)
    // Access Methods
    .method("halfedge", [](const VD::Face& f) { return *f.halfedge(); })
    .method("ccb", [](const VD::Face& f) {
      return collect<VD::Halfedge>(f.ccb());
    })
    .method("dual", [](const VD::Face& f) { return *f.dual();     })
    // Predicate Methods
    .METHOD(VD::Face, is_unbounded)
    .method("is_halfedge_on_ccb", [](const VD::Face& f, const VD::Halfedge& hf) {
      return f.is_halfedge_on_ccb(VD::Halfedge_handle(hf));
    })
    .METHOD(VD::Face, is_valid)
    ;

  vdhalfedge
    .CTOR(const VD::Halfedge&)
    OVERRIDE_BASE(cgal, vdhalfedge)
    .BINARY_OP_SELF(VD::Halfedge, ==)
    .BINARY_OP_SELF(VD::Halfedge,  <)
    UNSET_OVERRIDE(cgal, vdhalfedge)
    // Access Methods
    .method("twin",     [](const VD::Halfedge& he) { return *he.twin();     })
    .method("opposite", [](const VD::Halfedge& he) { return *he.opposite(); })
    .method("next",     [](const VD::Halfedge& hf) { return *hf.next();     })
    .method("previous", [](const VD::Halfedge& hf) { return *hf.previous(); })
    .method("face",     [](const VD::Halfedge& hf) { return *hf.face();     })
    .method("source",   [](const VD::Halfedge& hf) {
      return hf.has_source() ?
        (jl_value_t*)jlcxx::box<VD::Vertex>(*(hf.source())) :
        jl_nothing;
    })
    .method("target", [](const VD::Halfedge& hf) {
      return hf.has_target() ?
        (jl_value_t*)jlcxx::box<VD::Vertex>(*(hf.target())) :
        jl_nothing;
    })
    .method("ccb", [](const VD::Halfedge he) {
      return collect<VD::Halfedge>(he.ccb());
    })
    .METHOD(VD::Halfedge, dual)
    .method("up",    [](const VD::Halfedge he) { return *he.up();    })
    .method("down",  [](const VD::Halfedge he) { return *he.down();  })
    .method("left",  [](const VD::Halfedge he) { return *he.left();  })
    .method("right", [](const VD::Halfedge he) { return *he.right(); })
    // Predicate Methods
    .METHOD(VD::Halfedge, has_source)
    .METHOD(VD::Halfedge, has_target)
    .METHOD(VD::Halfedge, is_unbounded)
    .METHOD(VD::Halfedge, is_bisector)
    .METHOD(VD::Halfedge, is_segment)
    .METHOD(VD::Halfedge, is_ray)
    .METHOD(VD::Halfedge, is_valid)
    ;

  vdvertex
    .CTOR(const VD::Vertex&)
    OVERRIDE_BASE(cgal, vdvertex)
    .BINARY_OP_SELF(VD::Vertex, ==)
    .BINARY_OP_SELF(VD::Vertex,  <)
    UNSET_OVERRIDE(cgal, vdvertex)
    // Access Methods
    .method("halfedge", [](const VD::Vertex& v) { return *v.halfedge(); })
    .METHOD(VD::Vertex, degree)
    .METHOD(VD::Vertex, point)
    .method("dual", [](const VD::Vertex& v) { return *v.dual(); })
    .method("site", [](const VD::Vertex& v, unsigned int i) {
      return *v.site(i - 1);
    })
    .method("incident_halfedges", [](const VD::Vertex& v) {
      return collect<VD::Halfedge>(v.incident_halfedges());
    })
    // Predicate Methods
    .method("is_incident_edge", [](const VD::Vertex& v, const VD::Halfedge& hf) {
      return v.is_incident_edge(VD::Halfedge_handle(hf));
    })
    .method("is_incident_face", [](const VD::Vertex& v, const VD::Face& f) {
      return v.is_incident_face(VD::Face_handle(f));
    })
    .METHOD(VD::Vertex, is_valid)
    ;

  vd
    .CTOR(const DG&)
    .method(vd_name, [](jlcxx::ArrayRef<VD::Site_2> ss) {
      return jlcxx::create<VD>(ss.begin(), ss.end());
    })
    // Access Methods
    .UNAMBIG_METHOD(const DG&, VD, dual)
    .method("dual", [](const VD& vd, const DG::Edge& e) {
      return *vd.dual(e);
    })
    .METHOD(VD, number_of_vertices)
    .METHOD(VD, number_of_faces)
    .METHOD(VD, number_of_halfedges)
    .METHOD(VD, number_of_connected_components)
    // "Iterators"
    .method("faces", [](const VD& vd) {
      return collect<VD::Face>(vd.faces_begin(), vd.faces_end());
    })
    .method("unbounded_faces", [](const VD& vd) {
      return collect<VD::Face>(vd.unbounded_faces_begin(),
                               vd.unbounded_faces_end());
    })
    .method("bounded_faces", [](const VD& vd) {
      return collect<VD::Face>(vd.bounded_faces_begin(),
                               vd.bounded_faces_end());
    })
    .method("edges", [](const VD& vd) {
      return collect<VD::Halfedge>(vd.edges_begin(),
                                   vd.edges_end());
    })
    .method("halfedges", [](const VD& vd) {
      return collect<VD::Halfedge>(vd.halfedges_begin(),
                                   vd.halfedges_end());
    })
    .method("unbounded_halfedges", [](const VD& vd) {
      return collect<VD::Halfedge>(vd.unbounded_halfedges_begin(),
                                   vd.unbounded_halfedges_end());
    })
    .method("bounded_halfedges", [](const VD& vd) {
      return collect<VD::Halfedge>(vd.bounded_halfedges_begin(),
                                   vd.bounded_halfedges_end());
    })
    .method("vertices", [](const VD& vd) {
      return collect<VD::Vertex>(vd.vertices_begin(), vd.vertices_end());
    })
    .method("sites", [](const VD& vd) {
      return collect<VD::Site_2>(vd.sites_begin(), vd.sites_end());
    })
    // "Circulators"
    .method("ccb_halfedges", [](const VD& vd, const VD::Face& f) {
      return collect<VD::Halfedge>(vd.ccb_halfedges(VD::Face_handle(f)));
    })
    .method("ccb_halfedges", [](const VD& vd,
                                const VD::Face& f,
                                const VD::Halfedge& he) {
      return collect<VD::Halfedge>(vd.ccb_halfedges(VD::Face_handle(f),
                                                    VD::Halfedge_handle(he)));
    })
    .method("incident_halfedges", [](const VD& vd, const VD::Vertex& v) {
      return collect<VD::Halfedge>(vd.incident_halfedges(VD::Vertex_handle(v)));
    })
    .method("incident_halfedges", [](const VD& vd,
                                     const VD::Vertex& v,
                                     const VD::Halfedge& he) {
      return collect<VD::Halfedge>(
          vd.incident_halfedges(VD::Vertex_handle(v), VD::Halfedge_handle(he)));
    })
    // Insertion
    OVERRIDE_BASE(cgal, vd)
    .method("push!", [](VD& vd, const VD::Point_2& p) {
      vd.insert(p);
      return vd;
    })
    .method("insert!", [](VD& vd, jlcxx::ArrayRef<VD::Site_2> ps) {
      vd.insert(ps.begin(), ps.end());
      return vd;
    })
    .method("empty!", (VD& vd) {
      vd.clear();
      return vd;
    }) // Misc
    UNSET_OVERRIDE(cgal, vd)
    // Queries
    .method("locate", [](const VD& vd, const VD::Point_2& p) {
      return boost::apply_visitor(Handle_visitor(), vd.locate(p));
    })
    // Validity check
    .METHOD(VD, is_valid)
    // Miscellaneous
    .METHOD(VD, swap)
    ;
}
