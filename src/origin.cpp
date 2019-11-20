#include <type_traits>

#include <CGAL/Origin.h>

#include "origin.hpp"

template<> struct jlcxx::IsMirroredType<CGAL::Origin>      : std::false_type {};
template<> struct jlcxx::IsMirroredType<CGAL::Null_vector> : std::false_type {};

void wrap_origin(jlcxx::Module& cgal) {
  cgal.add_type<CGAL::Origin>("Origin");
  cgal.add_type<CGAL::Null_vector>("NullVector");
}
