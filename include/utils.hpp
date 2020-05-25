#ifndef CGAL_JL_UTILS_HPP
#define CGAL_JL_UTILS_HPP

#include <jlcxx/type_conversion.hpp>

template <typename T, typename InputIterator>
jlcxx::Array<T> collect(InputIterator begin, InputIterator end) {
  jlcxx::Array<T> jlarr;
  InputIterator it = begin;
  while (it != end) jlarr.push_back(*it++);
  return jlarr;
}

template<typename T, typename InputCirculator>
jlcxx::Array<T> collect(InputCirculator begin) {
  jlcxx::Array<T> jlarr;
  InputCirculator cc = begin;
  do jlarr.push_back(*cc); while(++cc != begin);
  return jlarr;
}

struct Handle_visitor {
  using result_type = jl_value_t*;

  template <typename Handle>
  result_type operator()(const Handle& h) const {
    return jlcxx::box<typename Handle::value_type>(*h);
  }
};

#endif // CGAL_JL_UTILS_HPP
