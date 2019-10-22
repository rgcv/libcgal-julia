#ifndef CGAL_JLCXX_KERNEL_HPP
#define CGAL_JLCXX_KERNEL_HPP

#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Origin.h>

#include <CGAL/aff_transformation_tags.h>
#include <CGAL/enum.h>

#include <jlcxx/jlcxx.hpp>

/// Kernel
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt Kernel;

/// Types
typedef Kernel::FT          FT;
// Redundant, since we're using a cartesian kernel (i.e. FT == RT)
typedef Kernel::RT          RT;

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

template<typename T>
double to_double(const T&);

#endif // CGAL_JLCXX_KERNEL_HPP
