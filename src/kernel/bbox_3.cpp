#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_bbox_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Bbox_3>& bbox_3) {
  bbox_3
    // Creation
    .constructor<double, double, double, double, double, double>()
    // Operations
    .method("dimension", &Bbox_3::dimension)
    .method("xmin",      &Bbox_3::xmin)
    .method("ymin",      &Bbox_3::ymin)
    .method("zmin",      &Bbox_3::zmin)
    .method("xmax",      &Bbox_3::xmax)
    .method("ymax",      &Bbox_3::ymax)
    .method("zmax",      &Bbox_3::zmax)
    ;
  kernel.set_override_module(jl_base_module);
  bbox_3
    .method("==",  &Bbox_3::operator==)
    .method("min", &Bbox_3::min)
    .method("max", &Bbox_3::max)
    .method("+",   &Bbox_3::operator+)
    ;
  kernel.unset_override_module();
  bbox_3
    .method("dilate", &Bbox_3::dilate)
    // Representation
    .TO_STRING(Bbox_3)
    ;
}

} // jlcgal
