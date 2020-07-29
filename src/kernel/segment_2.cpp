#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

namespace jlcgal {

void wrap_segment_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Segment_2>& segment_2) {
  segment_2
    // Creation
    .CTOR(const Point_2&, const Point_2&)
    // Operations
    OVERRIDE_BASE(kernel, segment_2)
    .BINARY_OP_SELF(const Segment_2&, ==)
    .METHOD(Segment_2, min            )
    .METHOD(Segment_2, max            )
    UNSET_OVERRIDE(kernel, segment_2)
    .METHOD(Segment_2, source         )
    .METHOD(Segment_2, target         )
    .METHOD(Segment_2, vertex         )
    .METHOD(Segment_2, point          )
    .METHOD(Segment_2, squared_length )
    .METHOD(Segment_2, direction      )
    .METHOD(Segment_2, to_vector      )
    .METHOD(Segment_2, opposite       )
    .METHOD(Segment_2, supporting_line)
    // Predicates
    .METHOD(Segment_2, is_degenerate   )
    .METHOD(Segment_2, is_horizontal   )
    .METHOD(Segment_2, is_vertical     )
    .METHOD(Segment_2, has_on          )
    .METHOD(Segment_2, collinear_has_on)
    // Miscellaneous
    .METHOD(Segment_2, bbox     )
    .METHOD(Segment_2, transform)
    // Representation
    .REPR(Segment_2)
    ;
}

} // jlcgal
