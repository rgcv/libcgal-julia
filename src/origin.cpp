#include <type_traits>

#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>
#include <jlcxx/type_conversion.hpp>

#include "macros.hpp"

void wrap_origin(jlcxx::Module& cgal) {
  CGAL_SMAP(Origin);
  CGAL_MAP(Null_vector, NullVector);
}
