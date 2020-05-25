#include <jlcxx/module.hpp>
#include <jlcxx/type_conversion.hpp>

#include <julia.h>

#include "macros.hpp"
#include "triangulation.hpp"
#include "utils.hpp"

#define WRAP_TRIANGULATION(T, JT) \
  /* Creation */ \
  CTOR(const T&) \
  .METHOD(T, swap) \
  /* Access Functions */ \
  .METHOD(T, dimension) \
  .METHOD(T, number_of_faces) \
  .METHOD(T, number_of_vertices) \
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
  /* Modifiers */ \
  OVERRIDE_BASE(cgal, JT) \
  .method("empty!", &T::clear) \
  .method("insert!", [](T& t, jlcxx::ArrayRef<T::Point> ps) { \
    t.insert(ps.begin(), ps.end()); \
    return t; \
  }) \
  .method("push!", [](T& t, const T::Point& p) { \
    t.push_back(p); \
    return t; \
  }) \
  UNSET_OVERRIDE(cgal, JT) \
  /* Finite Face, Edge and Vertex Iterators */ \
  .method("vertices", [](const T& t) { \
    return collect<T::Vertex>(t.vertices_begin(), t.vertices_end()); \
  }) \
  .method("edges", [](const T& t) { \
    return collect<T::Edge>(t.edges_begin(), t.edges_end()); \
  }) \
  .method("faces", [](const T& t) { \
    return collect<T::Face>(t.faces_begin(), t.faces_end()); \
  }) \
  .method("points", [](const T& t) { \
    return collect<T::Point>(t.points_begin(), t.points_end()); \
  }) \
  /* All Face, Edge and Vertex Iterators */ \
  .method("all_vertices", [](const T& t) { \
    return collect<T::Vertex>(t.all_vertices_begin(), t.all_vertices_end()); \
  }) \
  .method("all_edges", [](const T& t) { \
    return collect<T::Edge>(t.all_edges_begin(), t.all_edges_end()); \
  }) \
  .method("all_faces", [](const T& t) { \
    return collect<T::Face>(t.all_faces_begin(), t.all_faces_end()); \
  }) \
  /* Line Face Circulator */ \
  .method("line_walk", [](const T& t, const T::Point& p, const T::Point& q) { \
    return collect<T::Face>(t.line_walk(p, q)); \
  }) \
  /* Traversal Between Adjacent Faces */ \
  .METHOD(T, mirror_edge) \
  /* Miscellaneous */ \
  .UNAMBIG_METHOD(T::Segment, T, segment, const T::Edge&) \
  /* Checking */ \
  .METHOD(T, is_valid)

namespace jlcxx {
  template<> struct SuperType<CTr::Edge>   { using type = CTr::Triangulation::Edge; };
  template<> struct SuperType<CTr::Face>   { using type = CTr::Triangulation::Face; };
  template<> struct SuperType<CTr::Vertex> { using type = CTr::Triangulation::Vertex; };

  template<> struct SuperType<CDTr> { using type = CTr; };

  template<> struct SuperType<DTr>  { using type = Tr; };

  template<> struct SuperType<RTr::Edge>   { using type = RTr::Triangulation_base::Edge; };
  template<> struct SuperType<RTr::Face>   { using type = RTr::Triangulation_base::Face; };
  template<> struct SuperType<RTr::Vertex> { using type = RTr::Triangulation_base::Vertex; };
}

void wrap_triangulation_2(jlcxx::Module& cgal) {
  const std::string tr_name = "Triangulation2";
  auto tr      = cgal.add_type<Tr>        (tr_name);
  auto tedge   = cgal.add_type<Tr::Edge>  (tr_name + "Edge");
  auto tface   = cgal.add_type<Tr::Face>  (tr_name + "Face");
  auto tvertex = cgal.add_type<Tr::Vertex>(tr_name + "Vertex");

  const std::string ctr_name = "Constrained" + tr_name;
  cgal.add_type<CTr::Triangulation>(ctr_name + "Base");
  auto ctr      = cgal.add_type<CTr>        (ctr_name);
  auto ctedge   = cgal.add_type<CTr::Edge>  (ctr_name + "Edge",   tedge.dt());
  auto ctface   = cgal.add_type<CTr::Face>  (ctr_name + "Face",   tface.dt());
  auto ctvertex = cgal.add_type<CTr::Vertex>(ctr_name + "Vertex", tvertex.dt());

  auto cdtr = cgal.add_type<CDTr>("ConstrainedDelaunay" + tr_name, ctr.dt());

  const std::string dtr_name = "Delaunay" + tr_name;
  auto dtr = cgal.add_type<DTr>(dtr_name, tr.dt());

  const std::string rtr_name = "Regular" + tr_name;
  cgal.add_type<RTr::Triangulation_base>(rtr_name + "Base");
  auto rtr      = cgal.add_type<RTr>        (rtr_name);
  auto rtedge   = cgal.add_type<RTr::Edge>  (rtr_name + "Edge",   tedge.dt());
  auto rtface   = cgal.add_type<RTr::Face>  (rtr_name + "Face",   tface.dt());
  auto rtvertex = cgal.add_type<RTr::Vertex>(rtr_name + "Vertex", tvertex.dt());

  tvertex
    .METHOD(Tr::Vertex, degree)
    .UNAMBIG_METHOD(const Tr::Point&, Tr::Vertex, point)
    ;

  tface
    .METHOD(Tr::Face, dimension)
    .METHOD(Tr::Face, is_valid)
    .method("neighbor", [](const Tr::Face& f, int i) {
      return *f.neighbor(i - 1);
    })
    .method("vertex", [](const Tr::Face& f, int i) {
      return *f.vertex(i - 1);
    })
    ;

  tr
    .WRAP_TRIANGULATION(Tr, tr)
    .method(tr_name, [](jlcxx::ArrayRef<Tr::Point> ps) {
      return jlcxx::create<Tr>(ps.begin(), ps.end());
    })
    ;

  ctr
    .WRAP_TRIANGULATION(CTr, ctr)
    // Queries
    .METHOD(CTr, is_constrained)
    .method("constrained_edges", [](const CTr& ct) {
      return collect<CTr::Edge>(ct.constrained_edges_begin(),
                                ct.constrained_edges_end());
    })
    .method("insert_constraint", CAST_METHOD(void, CTr, insert_constraint,,
                                                        const CTr::Point&,
                                                        const CTr::Point&))
    .method("insert_constraint", [](CTr& ct, jlcxx::ArrayRef<CTr::Point> ps) {
      ct.insert_constraint(ps.begin(), ps.end());
    })
    ;

  cdtr
    // Creation
    .CTOR(const CDTr&)
    // Insertion and Removal
    OVERRIDE_BASE(cgal, cdtr)
    .method("insert!", [](CDTr& cdtr, jlcxx::ArrayRef<CDTr::Point> ps) {
      cdtr.insert(ps.begin(), ps.end());
      return cdtr;
    })
    .method("push!", [](CDTr& cdtr, const CDTr::Point& p) {
      cdtr.push_back(p);
      return cdtr;
    })
    UNSET_OVERRIDE(cgal, cdtr)
    // Miscellaneous
    .METHOD(CDTr, is_valid)
    ;

  dtr
    // Creation
    .CTOR(const DTr&)
    .method(dtr_name, [](jlcxx::ArrayRef<DTr::Point> ps) {
      return jlcxx::create<DTr>(ps.begin(), ps.end());
    })
    // Insertion and Removal
    OVERRIDE_BASE(cgal, dtr)
    .method("insert!", [](DTr& dt, jlcxx::ArrayRef<DTr::Point> ps) {
      dt.insert(ps.begin(), ps.end());
      return dt;
    })
    .method("push!", [](DTr& dt, const DTr::Point& p) {
      dt.push_back(p);
      return dt;
    })
    UNSET_OVERRIDE(cgal, dtr)
    // Queries
    .method("nearest_vertex", [](const DTr& dt, const DTr::Point& p) {
      return *dt.nearest_vertex(p);
    })
    // Voronoi Diagram
    .method("dual", [](const DTr& dt, const Tr::Edge& e) {
      auto&& o = dt.dual(e);

      if (const Line_2* l = CGAL::object_cast<Line_2>(&o)) {
        return (jl_value_t*)jlcxx::box<Line_2>(*l);
      } else if (const Ray_2* r = CGAL::object_cast<Ray_2>(&o)) {
        return (jl_value_t*)jlcxx::box<Ray_2>(*r);
      } else if (const Segment_2* s = CGAL::object_cast<Segment_2>(&o)) {
        return (jl_value_t*)jlcxx::box<Segment_2>(*s);
      }

      return jl_nothing; // unreachable
    })
    // Miscellaneous
    .METHOD(DTr, is_valid)
    ;

  rtvertex
    .UNAMBIG_METHOD(const RTr::Point&, RTr::Vertex, point)
    .METHOD(RTr::Vertex, is_hidden)
    .METHOD(RTr::Vertex, set_hidden)
    ;

  rtr
    .WRAP_TRIANGULATION(RTr, rtr)
    .method(rtr_name, [](jlcxx::ArrayRef<RTr::Point> ps) {
      return jlcxx::create<RTr>(ps.begin(), ps.end());
    })
    // Queries
    .method("nearest_power_vertex", [](const RTr& rt, const RTr::Bare_point& p) {
      return *rt.nearest_power_vertex(p);
    })
    // Access Functions
    .METHOD(RTr, number_of_hidden_vertices)
    .method("hidden_vertices", [](const RTr& rt) {
      return collect<RTr::Vertex>(rt.hidden_vertices_begin(),
                                  rt.hidden_vertices_end());
    })
    .method("finite_vertices", [](const RTr& rt) {
      return collect<RTr::Vertex>(rt.finite_vertices_begin(),
                                  rt.finite_vertices_end());
    })
    // Dual Power Diagram
    .method("dual", [](const RTr& rt, const RTr::Edge& e) {
      auto&& o = rt.dual(e);

      if (const Line_2* l = CGAL::object_cast<Line_2>(&o)) {
        return (jl_value_t*)jlcxx::box<Line_2>(*l);
      } else if (const Ray_2* r = CGAL::object_cast<Ray_2>(&o)) {
        return (jl_value_t*)jlcxx::box<Ray_2>(*r);
      } else if (const Segment_2* s = CGAL::object_cast<Segment_2>(&o)) {
        return (jl_value_t*)jlcxx::box<Segment_2>(*s);
      }

      return jl_nothing; // unreachable
    })
    ;
}

#undef WRAP_TRIANGULATION
