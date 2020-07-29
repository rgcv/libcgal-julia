#ifndef CGAL_JL_TRIANGULATION_HPP
#define CGAL_JL_TRIANGULATION_HPP

#include <CGAL/Triangulation_2.h>

#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>

#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/Regular_triangulation_2.h>

#include "kernel.hpp"

namespace jlcgal {

typedef CGAL::Triangulation_2<Kernel> Tr_2;

typedef CGAL::Constrained_triangulation_2<Kernel>          CTr_2;
typedef CGAL::Constrained_Delaunay_triangulation_2<Kernel> CDTr_2;

typedef CGAL::Delaunay_triangulation_2<Kernel> DTr_2;

typedef CGAL::Regular_triangulation_2<Kernel> RTr_2;

} // jlcgal

#endif // CGAL_JL_TRIANGULATION_HPP
