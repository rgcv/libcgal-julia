#ifndef CGAL_JLCXX_KERNEL_HPP
#define CGAL_JLCXX_KERNEL_HPP

#include <CGAL/Algebraic_kernel_for_circles_2_2.h>
#include <CGAL/Circular_kernel_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

/// Kernel
using LK = CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt;
using AK = CGAL::Algebraic_kernel_for_circles_2_2<LK::FT>;
using CK = CGAL::Circular_kernel_2<LK, AK>;
using K  = CK;

/// Types
using FT = K::FT;
using RT = K::RT; // same as FT for Cartesian kernels

/// 2D Kernel Objects
using Aff_transformation_2 = K::Aff_transformation_2;
using Bbox_2               = CGAL::Bbox_2;
using Circle_2             = K::Circle_2;
using Direction_2          = K::Direction_2;
using Iso_rectangle_2      = K::Iso_rectangle_2;
using Line_2               = K::Line_2;
using Point_2              = K::Point_2;
using Ray_2                = K::Ray_2;
using Segment_2            = K::Segment_2;
using Triangle_2           = K::Triangle_2;
using Vector_2             = K::Vector_2;
using Weighted_point_2     = K::Weighted_point_2;

#endif // CGAL_JLCXX_KERNEL_HPP
