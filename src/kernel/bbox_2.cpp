#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_bbox_2(jlcxx::Module& kernel, jlcxx::TypeWrapper<Bbox_2>& bbox_2) {
  bbox_2
    // Creation
    .CTOR(double, double, double, double)
    // Operations
    .METHOD(Bbox_2, dimension)
    .METHOD(Bbox_2, xmin     )
    .METHOD(Bbox_2, ymin     )
    .METHOD(Bbox_2, xmax     )
    .METHOD(Bbox_2, ymax     )
    OVERRIDE_BASE(kernel, bbox_2)
    .BINARY_OP_SELF(const Bbox_2&, ==)
    .METHOD(Bbox_2, min      )
    .METHOD(Bbox_2, max      )
    .BINARY_OP_SELF(const Bbox_2&,  +)
    UNSET_OVERRIDE(kernel, bbox_2)
    .METHOD(Bbox_2, dilate   )
    // Representation
    .TO_STRING(Bbox_2)
    ;
}

} // jlcgal
