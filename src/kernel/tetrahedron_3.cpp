#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

void wrap_tetrahedron_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Tetrahedron_3>& tetrahedron_3) {
  tetrahedron_3
    // Creation
    .CTOR(const Point_3&, const Point_3&, const Point_3&, const Point_3&)
    // Operations
    OVERRIDE_BASE(kernel, tetrahedron_3)
    .BINARY_OP_SELF(const Tetrahedron_3&, ==)
    UNSET_OVERRIDE(kernel, tetrahedron_3)
    .METHOD(Tetrahedron_3, vertex)
    // Predicates
    .METHOD(Tetrahedron_3, is_degenerate        )
    .METHOD(Tetrahedron_3, orientation          )
    .METHOD(Tetrahedron_3, oriented_side        )
    .METHOD(Tetrahedron_3, bounded_side         )
    // Convenience Boolean Functions
    .METHOD(Tetrahedron_3, has_on_positive_side )
    .METHOD(Tetrahedron_3, has_on_negative_side )
    .METHOD(Tetrahedron_3, has_on_boundary      )
    .METHOD(Tetrahedron_3, has_on_bounded_side  )
    .METHOD(Tetrahedron_3, has_on_unbounded_side)
    // Miscellaneous
    .METHOD(Tetrahedron_3, volume   )
    .METHOD(Tetrahedron_3, bbox     )
    .METHOD(Tetrahedron_3, transform)
    // Representation
    .REPR(Tetrahedron_3)
    ;
}

