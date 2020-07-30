#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_bbox_3(jlcxx::Module& kernel, jlcxx::TypeWrapper<Bbox_3>& bbox_3) {
  bbox_3
    // Creation
    .CTOR(double, double, double, double, double, double)
    // Operations
    .METHOD(Bbox_3, dimension)
    .METHOD(Bbox_3, xmin     )
    .METHOD(Bbox_3, ymin     )
    .METHOD(Bbox_3, zmin     )
    .METHOD(Bbox_3, xmax     )
    .METHOD(Bbox_3, ymax     )
    .METHOD(Bbox_3, zmax     )
    OVERRIDE_BASE(kernel, bbox_3)
    .BINARY_OP_SELF(const Bbox_3&, ==)
    .METHOD(Bbox_3, min      )
    .METHOD(Bbox_3, max      )
    .BINARY_OP_SELF(const Bbox_3&,  +)
    UNSET_OVERRIDE(kernel, bbox_3)
    .METHOD(Bbox_3, dilate   )
    // Representation
    .TO_STRING(Bbox_3)
    ;
}

} // jlcgal
