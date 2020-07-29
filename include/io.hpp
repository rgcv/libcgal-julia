#ifndef CGAL_JL_IO_HPP
#define CGAL_JL_IO_HPP

#include <sstream>

#include <CGAL/IO/io.h>

#define REPR(T) method("_tostring", &tostring<T>)

namespace jlcgal {

template<typename T>
inline
std::string tostring(const T &t) {
  std::ostringstream oss("");
  CGAL::set_pretty_mode(oss);
  oss << t;
  return oss.str();
}

} // jlcgal

#endif // CGAL_JL_IO_HPP
