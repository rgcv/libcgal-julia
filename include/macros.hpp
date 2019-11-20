#ifndef CGAL_JLCXX_MACROS_HPP
#define CGAL_JLCXX_MACROS_HPP

#define CAST_FUNC(R, F, ArgsT...) static_cast<R (*)(ArgsT)>(&F)
#define UNAMBIG_FUNC(R, F, ArgsT...) \
  method(#F, CAST_FUNC(R, CGAL::F, ArgsT))
#define FUNC(name, func) method(#name, &CGAL::func)
#define SIMPLE_FUNC(name) FUNC(name, name)
#define PFUNC(name, func, ArgsT...) method(#name, &CGAL::func<ArgsT>)
#define SIMPLE_PFUNC(name, ArgsT...) PFUNC(name, name, ArgsT)

#define CAST_MEMBER_METHOD(R, T, F, M, ArgsT...) \
  static_cast<R (T::*)(ArgsT) M>(&T::F)
#define METHOD(T, name) method(#name, &T::name)
#define UNAMBIG_METHOD(R, T, F, ArgsT...) \
  method(#F, CAST_MEMBER_METHOD(R, T, F, const, ArgsT))
#define INVOKE_METHOD(R, T, ArgsT...) \
  method(CAST_MEMBER_METHOD(R, T, operator(), const, ArgsT))

#define UNARY_OP(op, T) method(#op, [](T t) { return op t; })
#define BINARY_OP(T1, op, T2) \
  method(#op, [](T1 t1, T2 t2) { return t1 op t2; })
#define BINARY_OP_SELF(T, op) BINARY_OP(T, op, T)

#define GLOBAL_FUNCTION(R, F, ArgsT...) cgal.UNAMBIG_FUNC(R, F, ArgsT)

#endif // CGAL_JLCXX_MACROS_HPP
