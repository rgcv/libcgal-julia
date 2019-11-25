#ifndef CGAL_JLCXX_MACROS_HPP
#define CGAL_JLCXX_MACROS_HPP

#define CAST_FUNC(R, F, M, ArgsT...) static_cast<R (*)(ArgsT) M>(&F)
#define CAST_METHOD(R, T, F, M, ArgsT...) static_cast<R (T::*)(ArgsT) M>(&T::F)

#define TYPE_ST(T, N, ST) add_type<T>(#N, ST)
#define TYPE(T, N)  add_type<T>(#N)
#define STYPE(N)    TYPE(N, N)

#define CTOR(ArgsT...) constructor<ArgsT>()

#define UNAMBIG_FUNC(R, NS, F, ArgsT...) \
  method(#F, CAST_FUNC(R, NS::F,, ArgsT))
#define FUNC(NS, N, F) method(#N, &NS::F)
#define SFUNC(NS, F) FUNC(NS, F, F)
#define PFUNC(NS, N, F, ArgsT...) method(#N, &NS::F<ArgsT>)
#define SPFUNC(NS, F, ArgsT...) PFUNC(NS, F, F, ArgsT)

#define METHOD(T, N) SFUNC(T, N)
#define UNAMBIG_METHOD(R, T, F, ArgsT...) \
  method(#F, CAST_METHOD(R, T, F, const, ArgsT))
#define INVOKE_METHOD(R, T, ArgsT...) \
  method(CAST_METHOD(R, T, operator(), const, ArgsT))

#define UNARY_OP(op, T) method(#op, [](T t) { return op t; })
#define BINARY_OP(T1, op, T2) \
  method(#op, [](T1 t1, T2 t2) { return t1 op t2; })
#define BINARY_OP_SELF(T, op) BINARY_OP(T, op, T)

#define BITS_ST(T, N, ST) add_bits<T>(#N, ST)
#define BITS(T, N) add_bits<T>(#N)
#define SBITS(N)   BITS(N, N)
#define CONST(N, V) set_const(#N, V)

// CGAL specific
#define CGAL_TYPE(T, N) cgal.TYPE(CGAL::T, N)
#define CGAL_STYPE(N)   CGAL_TYPE(N, N)

#define CGAL_SIMPLE_PFUNC(F, ArgsT...) cgal.SPFUNC(CGAL, F, ArgsT)
#define CGAL_UNAMBIG_FUNC(R, F, ArgsT...) cgal.UNAMBIG_FUNC(R, CGAL, F, ArgsT)
#define CGAL_GLOBAL_FUNCTION(R, F, ArgsT...) \
  cgal.UNAMBIG_FUNC(R, CGAL, F, ArgsT)

#endif // CGAL_JLCXX_MACROS_HPP
