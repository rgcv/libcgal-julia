#include <CGAL/Origin.h>

#include <jlcxx/module.hpp>

namespace jlcgal {

void wrap_origin(jlcxx::Module& cgal) {
  cgal.map_type<CGAL::Origin>("Origin");
  cgal.map_type<CGAL::Null_vector>("NullVector");
}

} // jlcgal
