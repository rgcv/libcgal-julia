#ifndef CGAL_JL_TRIANGULATION_HPP
#define CGAL_JL_TRIANGULATION_HPP

#include <CGAL/Triangulation_2.h>

#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>

#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/Regular_triangulation_2.h>

#include "kernel.hpp"

namespace jlcgal {

using Tr_2   = CGAL::Triangulation_2<Kernel>;
using CTr_2  = CGAL::Constrained_triangulation_2<Kernel>;
using CDTr_2 = CGAL::Constrained_Delaunay_triangulation_2<Kernel>;
using DTr_2  = CGAL::Delaunay_triangulation_2<Kernel>;
using RTr_2  = CGAL::Regular_triangulation_2<Kernel>;

} // jlcgal

#endif // CGAL_JL_TRIANGULATION_HPP
