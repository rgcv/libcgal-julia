#include <jlcxx/module.hpp>

#include "kernel.hpp"
#include "macros.hpp"
#include "io.hpp"

void wrap_segment_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Segment_3>& segment_3) {
  segment_3
    // Creation
    .CTOR(const Point_3&, const Point_3&)
    // Operations
    OVERRIDE_BASE(kernel, segment_3)
    .BINARY_OP_SELF(const Segment_3&, ==)
    .METHOD(Segment_3, min)
    .METHOD(Segment_3, max)
    UNSET_OVERRIDE(kernel, segment_3)
    .METHOD(Segment_3, source        )
    .METHOD(Segment_3, target        )
    .METHOD(Segment_3, vertex        )
    .METHOD(Segment_3, point         )
    .METHOD(Segment_3, squared_length)
    .METHOD(Segment_3, to_vector     )
    .METHOD(Segment_3, direction)
    .METHOD(Segment_3, opposite      )
    .METHOD(Segment_3, supporting_line)
    .METHOD(Segment_3, is_degenerate )
    .METHOD(Segment_3, has_on        )
    .METHOD(Segment_3, bbox)
    .METHOD(Segment_3, transform)
    // Representation
    .REPR(Segment_3)
    ;
}
