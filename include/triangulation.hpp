#ifndef CGAL_JL_TRIANGULATION_HPP
#define CGAL_JL_TRIANGULATION_HPP

#include <CGAL/Triangulation_2.h>

#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>

#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/Regular_triangulation_2.h>

#include "kernel.hpp"

using Tr   = CGAL::Triangulation_2<Kernel>;
using CTr  = CGAL::Constrained_triangulation_2<Kernel>;
using CDTr = CGAL::Constrained_Delaunay_triangulation_2<Kernel>;
using DTr  = CGAL::Delaunay_triangulation_2<Kernel>;
using RTr  = CGAL::Regular_triangulation_2<Kernel>;

#endif // CGAL_JL_TRIANGULATION_HPP
