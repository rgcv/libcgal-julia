#include <jlcxx/module.hpp>

#include <julia.h>

#include "io.hpp"
#include "kernel.hpp"

namespace jlcgal {

void wrap_segment_3(jlcxx::Module& kernel,
    jlcxx::TypeWrapper<Segment_3>& segment_3) {
  segment_3
    // Creation
    .constructor<const Point_3&, const Point_3&>()
    ;
  kernel.set_override_module(jl_base_module);
  segment_3
    // Operations
    .method("==",  [](const Segment_3& s1, const Segment_3& s2) { return s1 == s2; })
    .method("min", &Segment_3::min)
    .method("max", &Segment_3::max)
    ;
  kernel.unset_override_module();
  segment_3
    .method("source",          &Segment_3::source)
    .method("target",          &Segment_3::target)
    .method("vertex",          &Segment_3::vertex)
    .method("point",           &Segment_3::point)
    .method("squared_length",  &Segment_3::squared_length)
    .method("to_vector",       &Segment_3::to_vector)
    .method("direction",       &Segment_3::direction)
    .method("opposite",        &Segment_3::opposite)
    .method("supporting_line", &Segment_3::supporting_line)
    .method("is_degenerate",   &Segment_3::is_degenerate)
    .method("has_on",          &Segment_3::has_on)
    .method("bbox",            &Segment_3::bbox)
    .method("transform",       &Segment_3::transform)
    // Representation
    .TO_STRING(Segment_3)
    ;
}

} // jlcgal
