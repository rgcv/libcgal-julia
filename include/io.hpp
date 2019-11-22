#ifndef CGAL_JLCXX_IO_HPP
#define CGAL_JLCXX_IO_HPP

#include <sstream>

#include <CGAL/IO/io.h>

#include "macros.hpp"

#define REPR(T) SPFUNC(repr,, T)

template<typename T>
inline
const std::string repr(const T &t) {
  std::ostringstream oss;
  CGAL::set_pretty_mode(oss);
  oss << t;
  return oss.str();
}

#endif // CGAL_JLCXX_IO_HPP
