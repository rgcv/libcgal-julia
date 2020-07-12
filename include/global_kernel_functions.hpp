#ifndef CGAL_JL_GLOBAL_KERNEL_FUNCTIONS_HPP
#define CGAL_JL_GLOBAL_KERNEL_FUNCTIONS_HPP

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/variant.hpp>

#include <jlcxx/type_conversion.hpp>

#include <julia.h>

#include "kernel.hpp"
#include "kernel_conversion.hpp"

typedef Circular_kernel  CK;
typedef Spherical_kernel SK;

struct Intersection_visitor {
  typedef jl_value_t* result_type;

  template<typename T>
  inline
  result_type
  operator()(const T& t) const {
    return jlcxx::box<T>(t);
  }

  template<typename... TS>
  inline
  result_type
  operator()(const boost::variant<TS...>& v) const {
    return boost::apply_visitor(*this, v);
  }

  template<typename T>
  result_type
  operator()(const std::vector<T>& ts) const {
    if (ts.empty()) {
      return jl_nothing;
    }

    const std::size_t sz = ts.size();
    result_type first = (*this)(ts[0]);

    if (sz == 1) {
      return first;
    }

    jl_value_t* atype = jl_apply_array_type(jl_typeof(first), 1);
    jl_array_t* ja = jl_alloc_array_1d(atype, sz);

    JL_GC_PUSH1(&ja);
    for (std::size_t i = 0; i < sz; ++i) {
      jl_arrayset(ja, (*this)(ts[i]), i);
    }
    JL_GC_POP();

    return (result_type)ja;
  }

  // Circular types
  inline
  result_type
  operator()(const std::pair<CK::Circular_arc_point_2, unsigned>& p) const {
    return jlcxx::box<Point_2>(To_linear<CK::Circular_arc_point_2>()(p.first));
  }

  inline
  result_type
  operator()(const CK::Circle_2& c) const {
    return jlcxx::box<Circle_2>(To_linear<CK::Circle_2>()(c));
  }

  // Spherical types
  inline
  result_type
  operator()(const std::pair<SK::Circular_arc_point_3, unsigned>& p) const {
    return jlcxx::box<Point_3>(To_linear<SK::Circular_arc_point_3>()(p.first));
  }

  #define SPHERICAL_VISITOR(T, ST) \
    inline \
    result_type \
    operator()(const SK::T& t) const { \
      return jlcxx::box<T>(To_linear<SK::ST>()(t)); \
    }
  #define SSPHERICAL_VISITOR(T) SPHERICAL_VISITOR(T, T)

  SSPHERICAL_VISITOR(Sphere_3)
  SSPHERICAL_VISITOR(Plane_3)
  SSPHERICAL_VISITOR(Line_3)
  SSPHERICAL_VISITOR(Circle_3)
  SPHERICAL_VISITOR(Segment_3, Line_arc_3)

  #undef SPHERICAL_VISITOR
  #undef SSPHERICAL_VISITOR
};

#endif // CGAL_JL_GLOBAL_KERNEL_FUNCTIONS_HPP
