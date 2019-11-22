#include <type_traits>

#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>
#include <jlcxx/type_conversion.hpp>

#include "macros.hpp"

template<> struct jlcxx::IsMirroredType<CGAL::Origin>      : std::false_type {};
template<> struct jlcxx::IsMirroredType<CGAL::Null_vector> : std::false_type {};

void wrap_origin(jlcxx::Module& cgal) {
  CGAL_STYPE(Origin);
  CGAL_TYPE(Null_vector, NullVector);
}
