#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_segment_2(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Segment_2>& segment_2) {
  segment_2
    // Creation
    .constructor<const Point_2&, const Point_2&>()
    ;
  kernel.set_override_module(jl_base_module);
  segment_2
    // Operations
    .method("==", &Segment_2::operator==)
    .method("min", &Segment_2::min)
    .method("max", &Segment_2::max)
    ;
  kernel.unset_override_module();
  segment_2
    .method("source",          &Segment_2::source)
    .method("target",          &Segment_2::target)
    .method("vertex",          &Segment_2::vertex)
    .method("point",           &Segment_2::point)
    .method("squared_length",  &Segment_2::squared_length)
    .method("direction",       &Segment_2::direction)
    .method("to_vector",       &Segment_2::to_vector)
    .method("opposite",        &Segment_2::opposite)
    .method("supporting_line", &Segment_2::supporting_line)
    // Predicates
    .method("is_degenerate",    &Segment_2::is_degenerate)
    .method("is_horizontal",    &Segment_2::is_horizontal)
    .method("is_vertical",      &Segment_2::is_vertical)
    .method("has_on",           &Segment_2::has_on)
    .method("collinear_has_on", &Segment_2::collinear_has_on)
    // Miscellaneous
    .method("bbox",      &Segment_2::bbox)
    .method("transform", &Segment_2::transform)
    // Representation
    .TO_STRING(Segment_2)
    ;
}

} // jlcgal
