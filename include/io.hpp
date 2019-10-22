#ifndef CGAL_JLCXX_IO_HPP
#define CGAL_JLCXX_IO_HPP

#include <CGAL/IO/io.h>

#include <sstream>

template<typename T>
inline
const std::string repr(const T &t) {
  std::ostringstream oss;
  CGAL::set_pretty_mode(oss);
  oss << t;
  return oss.str();
}

#endif // CGAL_JLCXX_IO_HPP
