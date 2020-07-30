#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_iso_rectangle_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Iso_rectangle_2>& iso_rectangle_2) {
  iso_rectangle_2
    // Creation
    .CTOR(const Point_2&, const Point_2&)
    .CTOR(const Point_2&, const Point_2&, int)
    .CTOR(const Point_2&, const Point_2&, const Point_2&, const Point_2&)
    .CTOR(const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&, const RT&)
    .CTOR(const Bbox_2&)
    // Operations
    OVERRIDE_BASE(kernel, iso_rectangle_2)
    .BINARY_OP_SELF(const Iso_rectangle_2&, ==)
    .METHOD(Iso_rectangle_2, min      )
    .METHOD(Iso_rectangle_2, max      )
    UNSET_OVERRIDE(kernel, iso_rectangle_2)
    .METHOD(Iso_rectangle_2, vertex   )
    .METHOD(Iso_rectangle_2, xmin     )
    .METHOD(Iso_rectangle_2, ymin     )
    .METHOD(Iso_rectangle_2, xmax     )
    .METHOD(Iso_rectangle_2, ymax     )
    .METHOD(Iso_rectangle_2, min_coord)
    .METHOD(Iso_rectangle_2, max_coord)
    // Predicates
    .METHOD(Iso_rectangle_2, is_degenerate        )
    .METHOD(Iso_rectangle_2, bounded_side         )
    .METHOD(Iso_rectangle_2, has_on_boundary      )
    .METHOD(Iso_rectangle_2, has_on_bounded_side  )
    .METHOD(Iso_rectangle_2, has_on_unbounded_side)
    // Miscellaneous
    .METHOD(Iso_rectangle_2, area     )
    .METHOD(Iso_rectangle_2, bbox     )
    .METHOD(Iso_rectangle_2, transform)
    // Representation
    .TO_STRING(Iso_rectangle_2)
    ;
}

} // jlcgal
