#ifndef CGAL_JLCXX_KERNEL_HPP
#define CGAL_JLCXX_KERNEL_HPP

#include <CGAL/Algebraic_kernel_for_circles_2_2.h>
#include <CGAL/Circular_kernel_2.h>

/// Kernel
#ifdef JLCGAL_EXACT_CONSTRUCTIONS
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt Linear_kernel;
#else
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel         Linear_kernel;
#endif

typedef CGAL::Algebraic_kernel_for_circles_2_2<Linear_kernel::FT> Algebraic_kernel;
typedef CGAL::Circular_kernel_2<Linear_kernel, Algebraic_kernel> Circular_kernel;

typedef Circular_kernel Kernel;

/// 2D Kernel Objects
typedef Kernel::Aff_transformation_2 Aff_transformation_2;
typedef CGAL::Bbox_2                 Bbox_2;
typedef Kernel::Circle_2             Circle_2;
typedef Kernel::Direction_2          Direction_2;
typedef Kernel::Iso_rectangle_2      Iso_rectangle_2;
typedef Kernel::Line_2               Line_2;
typedef Kernel::Point_2              Point_2;
typedef Kernel::Ray_2                Ray_2;
typedef Kernel::Segment_2            Segment_2;
typedef Kernel::Triangle_2           Triangle_2;
typedef Kernel::Vector_2             Vector_2;
typedef Kernel::Weighted_point_2     Weighted_point_2;

#endif // CGAL_JLCXX_KERNEL_HPP
