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
    .method("number_of_faces", &T::number_of_faces) \
    .method("number_of_vertices", &T::number_of_vertices) \
    /* Queries */ \
    .method("locate", [](const T& t, const T::Point& query) { \
      T::Face_handle fh = t.locate(query); \
      return fh != nullptr ? \
        (jl_value_t*)jlcxx::box<T::Face>(*fh) : \
        jl_nothing; \
    }) \
    .method("inexact_locate", [](const T& t, const T::Point& query) { \
      T::Face_handle fh = t.inexact_locate(query); \
      return fh != nullptr ? \
        (jl_value_t*)jlcxx::box<T::Face>(*fh) : \
        jl_nothing; \
    }) \
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
    .method("push!", [](T& t, const T::Point& p) -> T& { \
      t.push_back(p); \
      return t; \
    }) \
    ; \
  cgal.unset_override_module(); \
  JT \
    /* Finite Face, Edge and Vertex Iterators */ \
    .method("vertices", [](const T& t) { \
      return collect(t.vertices_begin(), t.vertices_end()); \
    }) \
    .method("edges", [](const T& t) { \
      return collect(t.edges_begin(), t.edges_end()); \
    }) \
    .method("faces", [](const T& t) { \
      return collect(t.faces_begin(), t.faces_end()); \
    }) \
    .method("points", [](const T& t) { \
      return collect(t.points_begin(), t.points_end()); \
    }) \
    /* All Face, Edge and Vertex Iterators */ \
    .method("all_vertices", [](const T& t) { \
      return collect(t.all_vertices_begin(), t.all_vertices_end()); \
    }) \
    .method("all_edges", [](const T& t) { \
      return collect(t.all_edges_begin(), t.all_edges_end()); \
    }) \
    .method("all_faces", [](const T& t) { \
      return collect(t.all_faces_begin(), t.all_faces_end()); \
    }) \
    /* Line Face Circulator */ \
    .method("line_walk", [](const T& t, const T::Point& p, const T::Point& q) { \
      return collect(t.line_walk(p, q)); \
    }) \
    /* Traversal Between Adjacent Faces */ \
    .method("mirror_edge", &T::mirror_edge) \
    /* Miscellaneous */ \
    .method("segment", [](const T& t, const T::Edge& e) { return t.segment(e); }) \
    /* Checking */ \
    .method("is_valid", &T::is_valid)

namespace jlcxx {
  using namespace jlcgal;

  template<> struct SuperType<DTr_3>  { typedef Tr_3 type; };

  template<> struct SuperType<RTr_3::Edge>   { typedef RTr_3::Tr_Base::Edge type; };
  template<> struct SuperType<RTr_3::Face>   { typedef RTr_3::Tr_Base::Face type; };
  template<> struct SuperType<RTr_3::Vertex> { typedef RTr_3::Tr_Base::Vertex type; };
}

namespace jlcgal {

void wrap_triangulation_3(jlcxx::Module& cgal) {
  const std::string tr_name = "Triangulation3";
  auto tr      = cgal.add_type<Tr_3>        (tr_name);
  auto tedge   = cgal.add_type<Tr_3::Edge>  (tr_name + "Edge");
  auto tface   = cgal.add_type<Tr_3::Face>  (tr_name + "Face");
  auto tvertex = cgal.add_type<Tr_3::Vertex>(tr_name + "Vertex");

  const std::string dtr_name = "Delaunay" + tr_name;
  auto dtr = cgal.add_type<DTr_3>(dtr_name, tr.dt());

  const std::string rtr_name = "Regular" + tr_name;
  cgal.add_type<RTr_3::Tr_Base>(rtr_name + "Base");
  auto rtr      = cgal.add_type<RTr_3>        (rtr_name);
  auto rtedge   = cgal.add_type<RTr_3::Edge>  (rtr_name + "Edge",   tedge.dt());
  auto rtface   = cgal.add_type<RTr_3::Face>  (rtr_name + "Face",   tface.dt());
  auto rtvertex = cgal.add_type<RTr_3::Vertex>(rtr_name + "Vertex", tvertex.dt());

  tvertex
    .method("degree", &Tr_3::Vertex::degree)
    .method("point", [](const Tr_3::Vertex& v) -> const Tr_3::Point& {
      return v.point();
    })
    ;

  tface
    .method("dimension", &Tr_3::Face::dimension)
    .method("is_valid", &Tr_3::Face::is_valid)
    .method("neighbor", [](const Tr_3::Face& f, const jlcxx::cxxint_t i) {
      return *f.neighbor(i - 1);
    })
    .method("vertex", [](const Tr_3::Face& f, const jlcxx::cxxint_t i) {
      return *f.vertex(i - 1);
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
    .method("push!", [](DTr_3& dt, const DTr_3::Point& p) -> DTr_3& {
      dt.push_back(p);
      return dt;
    })
    ;
  cgal.unset_override_module();
  dtr
    // Queries
    .method("nearest_vertex", [](const DTr_3& dt, const DTr_3::Point& p) {
      return *dt.nearest_vertex(p);
    })
    // Voronoi Diagram
    .method("dual", [](const DTr_3& dt, const Tr_3::Edge& e) {
      auto&& o = dt.dual(e);

      if (const Line_3* l = CGAL::object_cast<Line_3>(&o)) {
        return (jl_value_t*)jlcxx::box<Line_3>(*l);
      } else if (const Ray_3* r = CGAL::object_cast<Ray_3>(&o)) {
        return (jl_value_t*)jlcxx::box<Ray_3>(*r);
      } else if (const Segment_3* s = CGAL::object_cast<Segment_3>(&o)) {
        return (jl_value_t*)jlcxx::box<Segment_3>(*s);
      }

      return jl_nothing; // unreachable
    })
    // Miscellaneous
    .method("is_valid", &DTr_3::is_valid)
    ;

  rtvertex
    .method("point", [](const RTr_3::Vertex& v) -> const RTr_3::Point& {
      return v.point();
    })
    .method("is_hidden",  &RTr_3::Vertex::is_hidden)
    .method("set_hidden", &RTr_3::Vertex::set_hidden)
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
    // Access Functions
    .method("number_of_hidden_vertices", &RTr_3::number_of_hidden_vertices)
    .method("hidden_vertices", [](const RTr_3& rt) {
      return collect(rt.hidden_vertices_begin(), rt.hidden_vertices_end());
    })
    .method("finite_vertices", [](const RTr_3& rt) {
      return collect(rt.finite_vertices_begin(), rt.finite_vertices_end());
    })
    // Dual Power Diagram
    .method("dual", [](const RTr_3& rt, const RTr_3::Edge& e) {
      auto&& o = rt.dual(e);

      if (const Line_3* l = CGAL::object_cast<Line_3>(&o)) {
        return (jl_value_t*)jlcxx::box<Line_3>(*l);
      } else if (const Ray_3* r = CGAL::object_cast<Ray_3>(&o)) {
        return (jl_value_t*)jlcxx::box<Ray_3>(*r);
      } else if (const Segment_3* s = CGAL::object_cast<Segment_3>(&o)) {
        return (jl_value_t*)jlcxx::box<Segment_3>(*s);
      }

      return jl_nothing; // unreachable
    })
    ;
}

#undef WRAP_TRIANGULATION

} // jlcgal
