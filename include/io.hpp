#ifndef CGAL_JL_IO_HPP
#define CGAL_JL_IO_HPP

#include <sstream>

#include <CGAL/IO/io.h>

#define TO_STRING(T) method("_tostring", &jlcgal::to_string<T>)

namespace jlcgal {

template<typename T>
inline
std::string to_string(const T &t) {
  std::ostringstream oss("");
  CGAL::set_pretty_mode(oss);
  oss << t;
  return oss.str();
}

} // jlcgal

#endif // CGAL_JL_IO_HPP
