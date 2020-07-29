#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_iso_cuboid_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Iso_cuboid_3>& iso_cuboid_3) {
  iso_cuboid_3
    // Creation
    .CTOR(const Point_3&, const Point_3&)
    .CTOR(const Point_3&, const Point_3&, int)
    .CTOR(const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&, const Point_3&)
    .CTOR(const RT&, const RT&, const RT&, const RT&, const RT&, const RT&)
    .CTOR(const RT&, const RT&, const RT&, const RT&, const RT&, const RT&, const RT&)
    .CTOR(const Bbox_3&)
    // Operations
    OVERRIDE_BASE(kernel, iso_cuboid_3)
    .BINARY_OP_SELF(const Iso_cuboid_3&, ==)
    .METHOD(Iso_cuboid_3, min      )
    .METHOD(Iso_cuboid_3, max      )
    UNSET_OVERRIDE(kernel, iso_cuboid_3)
    .METHOD(Iso_cuboid_3, vertex   )
    .METHOD(Iso_cuboid_3, xmin     )
    .METHOD(Iso_cuboid_3, ymin     )
    .METHOD(Iso_cuboid_3, zmin     )
    .METHOD(Iso_cuboid_3, xmax     )
    .METHOD(Iso_cuboid_3, ymax     )
    .METHOD(Iso_cuboid_3, zmax     )
    .METHOD(Iso_cuboid_3, min_coord)
    .METHOD(Iso_cuboid_3, max_coord)
    // Predicates
    .METHOD(Iso_cuboid_3, is_degenerate        )
    .METHOD(Iso_cuboid_3, bounded_side         )
    .METHOD(Iso_cuboid_3, has_on_boundary      )
    .METHOD(Iso_cuboid_3, has_on_bounded_side  )
    .METHOD(Iso_cuboid_3, has_on_unbounded_side)
    // Miscellaneous
    .METHOD(Iso_cuboid_3, volume   )
    .METHOD(Iso_cuboid_3, bbox     )
    .METHOD(Iso_cuboid_3, transform)
    // Representation
    .REPR(Iso_cuboid_3)
    ;
}

} // jlcgal
