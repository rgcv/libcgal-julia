#ifndef CGAL_JLCXX_ENUM_HPP
#define CGAL_JLCXX_ENUM_HPP

#include <CGAL/enum.h>

namespace jlcxx {
  template<> struct IsBits<CGAL::Angle>                 : std::true_type {};
  template<> struct IsBits<CGAL::Bounded_side>          : std::true_type {};
  template<> struct IsBits<CGAL::Box_parameter_space_2> : std::true_type {}; 
  // Covers Comparison_result, Orientation, and Oriented_side
  template<> struct IsBits<CGAL::Sign> : std::true_type {};
}

#endif //CGAL_JLCXX_ENUM_HPP
