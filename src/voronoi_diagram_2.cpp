#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Regular_triangulation_adaptation_policies_2.h>
#include <CGAL/Regular_triangulation_adaptation_traits_2.h>
#include <CGAL/Voronoi_diagram_2.h>

#include <jlcxx/module.hpp>

#include <julia.h>

#include "triangulation.hpp"
#include "utils.hpp"

namespace jlcxx {
  template<typename DG, typename AT, typename AP>
  struct BuildParameterList<CGAL::Voronoi_diagram_2<DG, AT, AP>> {
    typedef ParameterList<DG> type;
  };
};

namespace jlcgal {

template<typename DT2>
using Voronoi_delaunay_2 = CGAL::Voronoi_diagram_2<DT2
  , CGAL::Delaunay_triangulation_adaptation_traits_2<DT2>
  , CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT2>>;

template<typename RT2>
using Voronoi_regular_2 = CGAL::Voronoi_diagram_2<RT2
  , CGAL::Regular_triangulation_adaptation_traits_2<RT2>
  , CGAL::Regular_triangulation_caching_degeneracy_removal_policy_2<RT2>>;


void wrap_voronoi_diagram_2(jlcxx::Module& cgal) {
  using jlcxx::Parametric;
  using jlcxx::TypeVar;

  const std::string vd_name = "VoronoiDiagram2";

  auto vdface     = cgal.add_type<Parametric<TypeVar<1>>>(vd_name + "Face");
  auto vdhalfedge = cgal.add_type<Parametric<TypeVar<1>>>(vd_name + "Halfedge");
  auto vdvertex   = cgal.add_type<Parametric<TypeVar<1>>>(vd_name + "Vertex");

  cgal.add_type<Parametric<TypeVar<1>>>(vd_name)
    .apply<Voronoi_delaunay_2<DTr_2>, Voronoi_regular_2<RTr_2>>([&](auto vd) {
      typedef typename decltype(vd)::type  VD;
      typedef typename VD::Delaunay_graph  DG;
      typedef typename VD::Face            Face;
      typedef typename VD::Face_handle     Face_handle;
      typedef typename VD::Halfedge        Halfedge;
      typedef typename VD::Halfedge_handle Halfedge_handle;
      typedef typename VD::Point_2         Point_2;
      typedef typename VD::Site_2          Site_2;
      typedef typename VD::Vertex          Vertex;
      typedef typename VD::Vertex_handle   Vertex_handle;

      vdface.template apply<Face>([](auto face) {
        face.
          template constructor<const Face&>()
          ;
        face.module().set_module_override(jl_base_module);
        face
          .method("==", &Face::operator==)
          .method("<",  &Face::operator<)
          ;
        face.module().unset_module_override();
        face
          // Predicate Methods
          .method("is_unbounded", &Face::is_unbounded)
          .method("is_valid",     &Face::is_valid)
          ;
      });

      vdhalfedge.template apply<Halfedge>([](auto halfedge) {
        halfedge
          .template constructor<const Halfedge&>()
          ;
        halfedge.module().set_module_override(jl_base_module);
        halfedge
          .method("==", &Halfedge::operator==)
          .method("<",  &Halfedge::operator<)
          ;
        halfedge.module().unset_module_override();
        halfedge
          // Access Methods
          .method("twin",     [](const Halfedge& he) { return *he.twin();     })
          .method("opposite", [](const Halfedge& he) { return *he.opposite(); })
          .method("next",     [](const Halfedge& he) { return *he.next();     })
          .method("previous", [](const Halfedge& he) { return *he.previous(); })
          .method("face",     [](const Halfedge& he) { return *he.face();     })
          .method("ccb",      [](const Halfedge& he) { return collect(he.ccb()); })
          .method("dual", &Halfedge::dual)
          .method("up",       [](const Halfedge& he) { return *he.up();    })
          .method("down",     [](const Halfedge& he) { return *he.down();  })
          .method("left",     [](const Halfedge& he) { return *he.left();  })
          .method("right",    [](const Halfedge& he) { return *he.right(); })
          // Predicate Methods
          .method("has_source",   &Halfedge::has_source)
          .method("has_target",   &Halfedge::has_target)
          .method("is_unbounded", &Halfedge::is_unbounded)
          .method("is_bisector",  &Halfedge::is_bisector)
          .method("is_segment",   &Halfedge::is_segment)
          .method("is_ray",       &Halfedge::is_ray)
          .method("is_valid",     &Halfedge::is_valid)
          ;
      });

      vdface
        // Access Methods
        .method("halfedge", [](const Face& f) { return *f.halfedge();    })
        .method("ccb",      [](const Face& f) { return collect(f.ccb()); })
        .method("dual",     [](const Face& f) { return *f.dual();        })
        // Predicate Methods
        .method("is_halfedge_on_ccb", [](const Face& f, const Halfedge& hf) {
          return f.is_halfedge_on_ccb(Halfedge_handle(hf));
        })
        ;

       vdvertex.template apply<Vertex>([](auto vertex) {
        typedef typename Vertex::Face            Face;
        typedef typename Vertex::Face_handle     Face_handle;
        typedef typename Vertex::Halfedge        Halfedge;
        typedef typename Vertex::Halfedge_handle Halfedge_handle;

        vertex
          .template constructor<const Vertex&>()
          ;
        vertex.module().set_override_module(jl_base_module);
        vertex
          .method("==", &Vertex::operator==)
          .method("<",  &Vertex::operator<)
          ;
        vertex.module().unset_override_module();
        vertex
          // Access Methods
          .method("halfedge", [](const Vertex& v) { return *v.halfedge(); })
          .method("degree", &Vertex::degree)
          .method("point", &Vertex::point)
          .method("dual", [](const Vertex& v) { return *v.dual(); })
          .method("site", [](const Vertex& v, const jlcxx::cxxint_t i) {
            return *v.site(i - 1);
          })
          .method("incident_halfedges", [](const Vertex& v) {
            return collect(v.incident_halfedges());
          })
          // Predicate Methods
          .method("is_incident_edge", [](const Vertex& v, const Halfedge& hf) {
            return v.is_incident_edge(Halfedge_handle(hf));
          })
          .method("is_incident_face", [](const Vertex& v, const Face& f) {
            return v.is_incident_face(Face_handle(f));
          })
          .method("is_valid", &Vertex::is_valid)
          ;
      });

      vdhalfedge
        // Access Methods
        .method("source",   [](const Halfedge& he) {
          return he.has_source() ?
            (jl_value_t*)jlcxx::box<Vertex>(*(he.source())) :
            jl_nothing;
        })
        .method("target", [](const Halfedge& he) {
          return he.has_target() ?
            (jl_value_t*)jlcxx::box<Vertex>(*(he.target())) :
            jl_nothing;
        })
        ;

      vd
        .template constructor<const DG&>()
        .method(vd_name, [](jlcxx::ArrayRef<Site_2> ss) {
          return jlcxx::create<VD>(ss.begin(), ss.end());
        })
        // Access Methods
        .method("dual", static_cast<const DG& (VD::*)() const>(&VD::dual))
        .method("dual", [](const VD& vd, const typename DG::Edge& e) {
          return *vd.dual(e);
        })
        .method("number_of_vertices",             &VD::number_of_vertices)
        .method("number_of_faces",                &VD::number_of_faces)
        .method("number_of_halfedges",            &VD::number_of_halfedges)
        .method("number_of_connected_components", &VD::number_of_connected_components)
        // "Iterators"
        .method("faces", [](const VD& vd) {
          return collect(vd.faces_begin(), vd.faces_end());
        })
        .method("unbounded_faces", [](const VD& vd) {
          return collect(vd.unbounded_faces_begin(), vd.unbounded_faces_end());
        })
        .method("bounded_faces", [](const VD& vd) {
          return collect(vd.bounded_faces_begin(), vd.bounded_faces_end());
        })
        .method("edges", [](const VD& vd) {
          return collect(vd.edges_begin(), vd.edges_end());
        })
        .method("halfedges", [](const VD& vd) {
          return collect(vd.halfedges_begin(), vd.halfedges_end());
        })
        .method("unbounded_halfedges", [](const VD& vd) {
          return collect(vd.unbounded_halfedges_begin(),
                         vd.unbounded_halfedges_end());
        })
        .method("bounded_halfedges", [](const VD& vd) {
          return collect(vd.bounded_halfedges_begin(),
                         vd.bounded_halfedges_end());
        })
        .method("vertices", [](const VD& vd) {
          return collect(vd.vertices_begin(), vd.vertices_end());
        })
        .method("sites", [](const VD& vd) {
          return collect(vd.sites_begin(), vd.sites_end());
        })
        // "Circulators"
        .method("ccb_halfedges", [](const VD& vd, const Face& f) {
          return collect(vd.ccb_halfedges(Face_handle(f)));
        })
        .method("ccb_halfedges", [](const VD& vd,
                                    const Face& f,
                                    const Halfedge& he) {
          return collect(vd.ccb_halfedges(Face_handle(f),
                                          Halfedge_handle(he)));
        })
        .method("incident_halfedges", [](const VD& vd, const Vertex& v) {
          return collect(vd.incident_halfedges(Vertex_handle(v)));
        })
        .method("incident_halfedges", [](const VD& vd,
                                         const Vertex& v,
                                         const Halfedge& he) {
          return collect(vd.incident_halfedges(Vertex_handle(v),
                                               Halfedge_handle(he)));
        })
        ;
      cgal.set_override_module(jl_base_module);
      vd
        // Insertion
        .method("push!", [](VD& vd, const Site_2& p) -> VD& {
          vd.insert(p);
          return vd;
        })
        .method("insert!", [](VD& vd, jlcxx::ArrayRef<Site_2> ps) -> VD& {
          vd.insert(ps.begin(), ps.end());
          return vd;
        })
        // Misc
        .method("empty!", [](VD& vd) -> VD& {
          vd.clear();
          return vd;
        })
        ;
      cgal.unset_override_module();
      vd
        // Queries
        .method("locate", [](const VD& vd, const Point_2& p) {
          return boost::apply_visitor(Handle_visitor(), vd.locate(p));
        })
        // Validity check
        .method("is_valid", &VD::is_valid)
        // Miscellaneous
        .method("swap", &VD::swap)
        ;
    });

}

} // jlcgal
