#include <jlcxx/module.hpp>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_bbox_2(jlcxx::Module& kernel, jlcxx::TypeWrapper<Bbox_2>& bbox_2) {
  bbox_2
    // Creation
    .constructor<double, double, double, double>()
    // Operations
    .method("dimension", &Bbox_2::dimension)
    .method("xmin",      &Bbox_2::xmin)
    .method("ymin",      &Bbox_2::ymin)
    .method("xmax",      &Bbox_2::xmax)
    .method("ymax",      &Bbox_2::ymax)
    ;
  kernel.set_override_module(jl_base_module);
  bbox_2
    .method("==",  &Bbox_2::operator==)
    .method("min", &Bbox_2::min)
    .method("max", &Bbox_2::max)
    .method("+",   &Bbox_2::operator+)
    ;
  kernel.unset_override_module();
  bbox_2
    .method("dilate", &Bbox_2::dilate)
    // Representation
    .TO_STRING(Bbox_2)
    ;
}

} // jlcgal
