#ifndef CGAL_JLCXX_MACROS_HPP
#define CGAL_JLCXX_MACROS_HPP

#define GLOBAL_FUNCTION(R, F, ArgsT...) \
  cgal.method(#F, static_cast<R(*)(ArgsT)>(&CGAL::F))

#endif // CGAL_JLCXX_MACROS_HPP
