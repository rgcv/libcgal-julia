#include <jlcxx/module.hpp>

namespace jlcgal {

void wrap_global_lk_functions(jlcxx::Module&);
void wrap_global_ck_functions(jlcxx::Module&);
void wrap_global_sk_functions(jlcxx::Module&);

void wrap_global_kernel_functions(jlcxx::Module& cgal) {
  wrap_global_lk_functions(cgal);
  wrap_global_ck_functions(cgal);
  wrap_global_sk_functions(cgal);
}

} // jlcgal
