# libcgal-julia

:warning: **DISCLAIMER** :warning: This project is still very young and, thus,
incredibly brittle and scarce. Currently, the kernel is being fixed on the C++
side of things. Currently, a circular kernel, backed by the
`Exact_predicates_exact_constructions_kernel_with_sqrt` 2D/3D kernel, is being
fixed, consequently fixing the kernel's constructs. This is a recognizable
limitation. Ideally, the appropriate non-aliased underlying kernels would be
made available as julia types, along with the multiple numeric types, and could
be used directly instead of being hidden away in the C++ side of things... One
can dream.

---

This library exposes a series of types and functions from [CGAL][1]
(Computational Geometry Algorithms Library) to the [julia][2] language. It
serves as the supporting library for the [CGAL.jl][3] package (not yet
published).

[CGAL][1] is a powerful easily-accessible C++ library that aims to provide
algorithms in computational geometry (hence the name) with emphasis on
reliability and efficiency while still providing robust results.

# Building

The project can be built using the `build_tarballs.jl` [`BinaryBuilder`][4] script
under `.github/scripts`. This is also used in CI and for publishing artifacts on
release. It can also be built manually, albeit discouraged since setting up the
required dependencies may be an arduous task.

## Using `build_tarballs.jl` (recommended)

You're only required to have `julia ≥ 1.0` installed. Once that requirement is
met, just run:

```sh
$ julia .github/scripts/build_tarballs.jl [optional,list,of,comma,separated,triplets]
```

You can provide a `--help` argument to get more information on `BinaryBuilder`'s
build script options. Check out [`BinaryBuilder.jl`][4] for more information.

By default, it will build for Windows (mingw) 32- and 64-bit architectures,
and GNU/Linux and MacOS 64-bit architectures. If you'd like to build for a
specific (set of) target(s), explicitly specify the targets you wish to build
for. For example, if you wish to build for Windows x86_64 using GCC 7 targetting
C++11 ABI upward, run:

```sh
$ julia .github/scripts/build_tarballs.jl x86_64-w64-mingw32-gcc7-cxx11
```

## Manually

Requirements:

- [`CMake`][5]
- [`CGAL = 5.0`][6]
  * [`Boost = 1.71`][7]
  * [`GMP`][8]
  * [`MPFR`][9]
- [`Julia ≥ 1.0`][10]
- [`JlCxx = 0.5.3`][11]

Depending on your system, it may be easier to aggregate and install the listed
requirements, with the exception of `JlCxx`, which, to my knowledge, isn't in
as readily available on any platform I've tested. However, the former ones are.
On Windows, (most) via neatly packed installers; on Linux & co., via the
distribution's package manager; on macOS, maybe homebrew, although I'm not sure.

Afterwards, it is a mostly typical run-of-the-mill CMake build:

```sh
mkdir build && cd build
cmake -DJlCxx_DIR=<path/to/libjlcxx-julia> ..
cmake --build . --target install
```

We can see above that `JlCxx_DIR` is specified. However, if it's reachable by
CMake, you won't need it.

# TODO

- [ ] Kernel
  - [ ] Objects
    - [x] 2D
    - [ ] 3D
    - [ ] Circular?
    - [ ] Spherical?
  - [ ] Global Functions
    - [x] 2D
    - [ ] 3D
    - [ ] Circular
    - [ ] Spherical
  - ...
- [ ] Type Parametrization?
- [ ] Iterators
- [ ] Circulators
- [ ] Other packages, such as
  - [ ] Convex Hulls
  - [ ] Voronoi Delaunay
  - ...

# Related Projects

- [cgal-swig-bindings][12] - CGAL bindings using SWIG
- [PYGAL - Python Geometric Algorithms Library][13] - CGAL python bindings using
  pybind11

[1]:  https://github.com/CGAL/cgal
[2]:  https://github.com/julialang/julia
[3]:  https://github.com/rgcv/CGAL.jl
[4]:  https://github.com/JuliaInterop/BinaryBuilder.jl
[5]:  https://github.com/Kitware/CMake/releases?after=3.13.2
[6]:  https://github.com/CGAL/cgal/releases/tag/releases%2FCGAL-4.14.1
[7]:  https://www.boost.org/users/history/version_1_71_0.html
[8]:  https://gmplib.org
[9]:  https://www.mpfr.org/mpfr-4.0.2
[10]: https://github.com/julialang/julia/releases/tag/v1.0.5
[11]: https://github.com/JuliaInterop/libcxxwrap-julia/releases/tag/v0.5.3
[12]: https://github.com/CGAL/cgal-swig-bindings
[13]: https://github.com/wolfv/pygal
