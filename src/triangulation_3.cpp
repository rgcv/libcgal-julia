#include <jlcxx/module.hpp>

#include <julia.h>

#include "utils.hpp"
#include "triangulation.hpp"

#define WRAP_TRIANGULATION(T, JT) \
    /* Creation */ \
     constructor<const T&>() \
    .method("swap", &T::swap) \
    /* Access Functions */ \
    .method("dimension", &T::dimension) \
    .method("number_of_facets", &T::number_of_facets) \
    .method("number_of_vertices", &T::number_of_vertices) \
    ; \
  cgal.set_override_module(jl_base_module); \
  JT \
    /* Modifiers */ \
    .method("empty!", [](T& t) -> T& { \
      t.clear(); \
      return t; \
    }) \
    .method("insert!", [](T& t, jlcxx::ArrayRef<T::Point> ps) -> T& { \
      t.insert(ps.begin(), ps.end()); \
      return t; \
    }) \
    ; \
  cgal.unset_override_module(); \
  JT \
    /* Finite Facet, Edge and Vertex Iterators */ \
    .method("vertices", [](const T& t) { \
      return collect(t.vertices_begin(), t.vertices_end()); \
    }) \
    .method("edges", [](const T& t) { \
      return collect(t.edges_begin(), t.edges_end()); \
    }) \
    .method("facets", [](const T& t) { \
      return collect(t.facets_begin(), t.facets_end()); \
    }) \
    .method("points", [](const T& t) { \
      return collect(t.points_begin(), t.points_end()); \
    }) \
    /* All Facet, Edge and Vertex Iterators */ \
    .method("all_vertices", [](const T& t) { \
      return collect(t.all_vertices_begin(), t.all_vertices_end()); \
    }) \
    .method("all_edges", [](const T& t) { \
      return collect(t.all_edges_begin(), t.all_edges_end()); \
    }) \
    .method("all_facets", [](const T& t) { \
      return collect(t.all_facets_begin(), t.all_facets_end()); \
    }) \
    /* Traversal Between Adjacent Facets */ \
    .method("mirror_facet", &T::mirror_facet) \
    /* Miscellaneous */ \
    .method("segment", [](const T& t, const T::Edge& e) { return t.segment(e); }) \

namespace jlcxx {
  using namespace jlcgal;

  template<> struct SuperType<DTr_3>  { typedef CGAL::Triangulation_3<Kernel, typename DTr_3::Triangulation_data_structure> type; };

  template<> struct SuperType<RTr_3::Edge>   { typedef RTr_3::Tr_Base::Edge type; };
  template<> struct SuperType<RTr_3::Facet>  { typedef RTr_3::Tr_Base::Facet type; };
  template<> struct SuperType<RTr_3::Vertex> { typedef RTr_3::Tr_Base::Vertex type; };
}

namespace jlcgal {

void wrap_triangulation_3(jlcxx::Module& cgal) {
  const std::string tr_name = "Triangulation3";
  auto tr      = cgal.add_type<Tr_3>        (tr_name);
  auto tedge   = cgal.add_type<Tr_3::Edge>  (tr_name + "Edge");
  auto tface   = cgal.add_type<Tr_3::Facet> (tr_name + "Facet");
  auto tvertex = cgal.add_type<Tr_3::Vertex>(tr_name + "Vertex");

  const std::string dtr_name = "Delaunay" + tr_name;
  auto dtr = cgal.add_type<DTr_3>(dtr_name, tr.dt());

  const std::string rtr_name = "Regular" + tr_name;
  cgal.add_type<RTr_3::Tr_Base>(rtr_name + "Base");
  auto rtr      = cgal.add_type<RTr_3>        (rtr_name);
  auto rtedge   = cgal.add_type<RTr_3::Edge>  (rtr_name + "Edge",   tedge.dt());
  auto rtface   = cgal.add_type<RTr_3::Facet> (rtr_name + "Facet",   tface.dt());
  auto rtvertex = cgal.add_type<RTr_3::Vertex>(rtr_name + "Vertex", tvertex.dt());

  tvertex
    .method("point", [](const Tr_3::Vertex& v) -> const Tr_3::Point& {
      return v.point();
    })
    ;

  tr
    .WRAP_TRIANGULATION(Tr_3, tr)
    .method(tr_name, [](jlcxx::ArrayRef<Tr_3::Point> ps) {
      return jlcxx::create<Tr_3>(ps.begin(), ps.end());
    })
    ;

  dtr
    // Creation
    .constructor<const DTr_3&>()
    .method(dtr_name, [](jlcxx::ArrayRef<DTr_3::Point> ps) {
      return jlcxx::create<DTr_3>(ps.begin(), ps.end());
    })
    ;
  cgal.set_override_module(jl_base_module);
  dtr
    // Insertion and Removal
    .method("insert!", [](DTr_3& dt, jlcxx::ArrayRef<DTr_3::Point> ps) -> DTr_3& {
      dt.insert(ps.begin(), ps.end());
      return dt;
    })
    ;
  cgal.unset_override_module();
  dtr
    // Queries
    .method("nearest_vertex", [](const DTr_3& dt, const DTr_3::Point& p) {
      return *dt.nearest_vertex(p);
    })
    ;

  rtvertex
    .method("point", [](const RTr_3::Vertex& v) -> const RTr_3::Point& {
      return v.point();
    })
    ;

  rtr
    .WRAP_TRIANGULATION(RTr_3, rtr)
    .method(rtr_name, [](jlcxx::ArrayRef<RTr_3::Point> ps) {
      return jlcxx::create<RTr_3>(ps.begin(), ps.end());
    })
    // Queries
    .method("nearest_power_vertex", [](const RTr_3& rt, const RTr_3::Bare_point& p) {
      return *rt.nearest_power_vertex(p);
    })
    .method("finite_vertices", [](const RTr_3& rt) {
      return collect(rt.finite_vertices_begin(), rt.finite_vertices_end());
    })
    ;
}

#undef WRAP_TRIANGULATION

} // jlcgal
