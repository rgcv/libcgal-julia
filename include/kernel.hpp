#ifndef CGAL_JL_KERNEL_HPP
#define CGAL_JL_KERNEL_HPP

#include <exception>

#include <CGAL/Algebraic_kernel_for_circles_2_2.h>
#include <CGAL/Circular_kernel_2.h>

/// Kernel
#ifdef JLCGAL_EXACT_CONSTRUCTIONS
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
using Linear_kernel = CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt;
#else
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
using Linear_kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
#endif

using Algebraic_kernel = CGAL::Algebraic_kernel_for_circles_2_2<Linear_kernel::FT>;
using Circular_kernel = CGAL::Circular_kernel_2<Linear_kernel, Algebraic_kernel>;

using Kernel = Circular_kernel;

using FT = Kernel::FT;
using RT = Kernel::RT;

/// 2D Kernel Objects
using Aff_transformation_2 = Kernel::Aff_transformation_2;
using Bbox_2               = CGAL::Bbox_2;
using Circle_2             = Kernel::Circle_2;
using Direction_2          = Kernel::Direction_2;
using Iso_rectangle_2      = Kernel::Iso_rectangle_2;
using Line_2               = Kernel::Line_2;
using Point_2              = Kernel::Point_2;
using Ray_2                = Kernel::Ray_2;
using Segment_2            = Kernel::Segment_2;
using Triangle_2           = Kernel::Triangle_2;
using Vector_2             = Kernel::Vector_2;
using Weighted_point_2     = Kernel::Weighted_point_2;

/// 2D Kernel Objects
using Plane_3   = Kernel::Plane_3;
using Point_3   = Kernel::Point_3;
using Segment_3 = Kernel::Segment_3;
using Vector_3  = Kernel::Vector_3;

template <typename T1, typename T2>
auto safe_division(const T1& t1, const T2& t2) -> decltype(t1/t2) {
  if (t2 == 0) throw std::overflow_error("division by zero");
  return t1 / t2;
}

#endif // CGAL_JL_KERNEL_HPP
