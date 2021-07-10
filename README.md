# libcgal-julia

This library exposes a series of types and functions from [CGAL][1]
(Computational Geometry Algorithms Library) to the
[julia](https://julialang.org) language.  It serves as the supporting library
for the [CGAL.jl](https://github.com/rgcv/CGAL.jl) package (not yet
published).

[CGAL][1] is a powerful easily-accessible C++ library that aims to provide
algorithms in computational geometry (hence the name) with emphasis on
reliability and efficiency while still providing robust results.

# Building

The project can be built manually, albeit discouraged since setting up the
required dependencies may be an arduous task.  Building the project for various
julia versions and platforms now is highly reliant on
[Yggdrasil](https://github.com/JuliaPackaging/Yggdrasil).

Currently, two shared libraries are being built: One with inexact constructions,
i.e., using the `Exact_predicates_inexact_constructions_kernel` linear kernel,
and another with exact constructions, i.e., using the
`Exact_predicates_exact_constructions_kernel_with_sqrt`, each library being
respectively suffixed with `_inexact` and `_exact`.  However, due to
pre-compilation, the current mechanism to swap between the two is made virtually
impossible.  Although still present in the source code, alternatives should be
looked into to support different kernels.  Ideally, support them with proper
templating instead of opaquely mapping kernel objects.

## Using `build_tarballs.jl` (outdated)

**NOTE**: This method is relatively outdated. It might work, but be warned.
YMMV. I haven't relied on it since adopting the `jll` artifacts system.

You're only required to have `julia ≥ 1.0` installed.  Once that requirement
is met, just run:

```sh
$ julia .github/scripts/build_tarballs.jl [optional,list,of,comma,separated,triplets]
```

You can provide a `--help` argument to get more information on
`BinaryBuilder`'s build script options.  Check out [`BinaryBuilder.jl`][2] for
more information.

By default, it will build for Windows (mingw) 32- and 64-bit architectures,
and GNU/Linux and MacOS 64-bit architectures.  If you'd like to build for a
specific (set of) target(s), explicitly specify the targets you wish to build
for.  For example, if you wish to build for Windows x86_64 using GCC 7
targetting C++11 ABI upward, run:

```sh
$ julia .github/scripts/build_tarballs.jl x86_64-w64-mingw32-gcc7-cxx11
```

## Manually

Requirements:

- [`CMake ≥ 3.14`](https://cmake.org/download/#latest)
- [`CGAL 5.3`](https://github.com/CGAL/cgal/releases/tag/v5.3)
  * [`Boost ≥ 1.66`](https://www.boost.org/users/history/version_1_66_0.html)
  * [`GMP ≥ 4.2`](https://gmplib.org/#DOWNLOAD)
  * [`MPFR ≥ 2.2.1`](https://www.mpfr.org/mpfr-current/)
- [`Julia ≥ 1.3`](https://julialang.org/downloads/)
- [`JlCxx ~0.8`](https://github.com/JuliaInterop/libcxxwrap-julia/releases/tag/v0.8.3)

Depending on your system, it may be easier to aggregate and install the
listed requirements, with the exception of `JlCxx`, which, to my knowledge,
isn't in as readily available on any platform I've tested.  However, the
former ones are.  On Windows, (most) via neatly packed installers; on Linux &
co., via the distribution's package manager; on macOS, maybe homebrew,
although I'm not sure.

Afterwards, it is a mostly typical run-of-the-mill CMake build:

```
cmake -B build -DJlCxx_DIR=<path/to/libcxxwrap-julia>
cmake --build build
```

We can see above that `JlCxx_DIR` is specified. However, if it's reachable by
CMake, you won't need it (i.e., libcxxwrap-julia is installed in your system in
a standard path).

# TODO

- [ ] Kernel
  - [x] Objects
  - [ ] Global Functions
    - [x] 2D
    - [x] 3D
    - [ ] Circular
    - [ ] Spherical
  - ...
- [ ] Type Parametrization?
- [ ] Iterators
- [ ] Circulators
- [ ] Other packages, such as
  - [x] 2D Convex Hulls
  - [ ] 3D Convex Hulls
  - [ ] 2D Voronoi Diagram
  - ...

# Related Projects

- [cgal-swig-bindings](https://github.com/CGAL/cgal-swig-bindings) - CGAL
  bindings using SWIG
- [scikit-geometry](https://github.com/scikit-geometry/scikit-geometry) -
  Scientific Python Geometric Algorithms Library (f.k.a. PYGAL, CGAL python
  bindings using pybind11 by [wolfv](https://github.com/wolfv)

[1]: https://github.com/CGAL/cgal
[2]: https://github.com/JuliaInterop/BinaryBuilder.jl
