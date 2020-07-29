#ifndef CGAL_JL_UTILS_HPP
#define CGAL_JL_UTILS_HPP

#include <jlcxx/type_conversion.hpp>

namespace jlcgal {

template <typename InputIterator>
decltype(auto)
collect(InputIterator begin, InputIterator end) {
  jlcxx::Array<typename InputIterator::value_type> jlarr;
  InputIterator it = begin;
  while (it != end) {
    jlarr.push_back(*it);
    ++it;
  }
  return jlarr;
}

template<typename InputCirculator>
decltype(auto)
collect(InputCirculator begin) {
  jlcxx::Array<typename InputCirculator::value_type> jlarr;
  InputCirculator cc = begin;
  do jlarr.push_back(*cc); while(++cc != begin);
  return jlarr;
}

struct Handle_visitor {
  typedef jl_value_t* result_type;

  template<typename Handle>
  result_type operator()(const Handle& h) const {
    return jlcxx::box<typename Handle::value_type>(*h);
  }
};

} // jlcgal

#endif // CGAL_JL_UTILS_HPP
