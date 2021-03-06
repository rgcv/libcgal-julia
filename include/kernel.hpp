#ifndef CGAL_JL_KERNEL_HPP
#define CGAL_JL_KERNEL_HPP

#include <exception>

#ifdef JLCGAL_EXACT_CONSTRUCTIONS
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#else
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#endif

#include <CGAL/Algebraic_kernel_for_circles_2_2.h>
#include <CGAL/Algebraic_kernel_for_spheres_2_3.h>
#include <CGAL/Circular_kernel_2.h>
#include <CGAL/Spherical_kernel_3.h>

namespace jlcgal {

/// Kernel
#ifdef JLCGAL_EXACT_CONSTRUCTIONS
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt Linear_kernel;
#else
typedef CGAL::Exact_predicates_inexact_constructions_kernel Linear_kernel;
#endif

typedef CGAL::Algebraic_kernel_for_circles_2_2<Linear_kernel::RT> Algebraic_kernel_2;
typedef CGAL::Algebraic_kernel_for_spheres_2_3<Linear_kernel::RT> Algebraic_kernel_3;
typedef CGAL::Circular_kernel_2<Linear_kernel, Algebraic_kernel_2> Circular_kernel;
typedef CGAL::Spherical_kernel_3<Linear_kernel, Algebraic_kernel_3> Spherical_kernel;

typedef Linear_kernel    Kernel;
typedef Circular_kernel  CK;
typedef Spherical_kernel SK;

typedef Kernel::FT FT;
typedef Kernel::RT RT;

/// 2D Kernel Objects
// Linear
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
// Circular
typedef Circular_kernel::Circular_arc_2 Circular_arc_2;

/// 3D Kernel Objects
// Linear
typedef Kernel::Aff_transformation_3 Aff_transformation_3;
typedef CGAL::Bbox_3                 Bbox_3;
typedef Kernel::Circle_3             Circle_3;
typedef Kernel::Direction_3          Direction_3;
typedef Kernel::Iso_cuboid_3         Iso_cuboid_3;
typedef Kernel::Line_3               Line_3;
typedef Kernel::Plane_3              Plane_3;
typedef Kernel::Point_3              Point_3;
typedef Kernel::Ray_3                Ray_3;
typedef Kernel::Segment_3            Segment_3;
typedef Kernel::Sphere_3             Sphere_3;
typedef Kernel::Tetrahedron_3        Tetrahedron_3;
typedef Kernel::Triangle_3           Triangle_3;
typedef Kernel::Vector_3             Vector_3;
typedef Kernel::Weighted_point_3     Weighted_point_3;
// Spherical
typedef Spherical_kernel::Circular_arc_3 Circular_arc_3;

template <typename T, typename U>
auto
safe_division(const T& t, const U& u) -> decltype(t / u) {
  if (u == 0) throw std::overflow_error("division by zero");
  return t / u;
}

} // jlcgal

#endif // CGAL_JL_KERNEL_HPP
