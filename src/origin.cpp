#include <CGAL/Origin.h>

#include "origin.hpp"

void wrap_origin(jlcxx::Module& cgal) {
  cgal.add_type<CGAL::Origin>("Origin");
  cgal.add_type<CGAL::Null_vector>("NullVector");
}
