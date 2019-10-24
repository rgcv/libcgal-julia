#ifndef CGAL_JLCXX_JLCXX_HPP
#define CGAL_JLCXX_JLCXX_HPP

#include <type_traits>

#include <CGAL/enum.h>

#include <jlcxx/type_conversion.hpp>

/// jlcxx type specialization for enums
namespace jlcxx {
  template<> struct IsBits<CGAL::Angle>        : std::true_type {};
  template<> struct IsBits<CGAL::Bounded_side> : std::true_type {};
  // Covers Comparison_result, Orientation, and Oriented_side
  template<> struct IsBits<CGAL::Sign> : std::true_type {};
}

#endif // CGAL_JLCXX_JLCXX_HPP
