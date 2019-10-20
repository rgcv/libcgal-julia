:warning: **DISCLAIMER** :warning: This project is still very young and, thus,
incredibly brittle and scarce. Currently, the kernel is being fixed on the C++
side of things. Currently, the
`Exact_predicates_exact_constructions_kernel_with_sqrt` 2D/3D kernel is being
fixed, consequently fixing the kernel's constructs. This limits the imense
toolset CGAL provides, namely, for example, the usage of the Circular kernel, or
the dD Kernel.

Ideally, julia types would be parametric, mirroring their respective template
types in CGAL, allowing for switching between any kind of kernel, seamlessly
using the underlying field and ring number types as if they were primitive
types. Alas, it isn't as simple as just making them parametric.

# libcgal-julia

This library exposes a series of types and functions from [CGAL][1]
(Computational Geometry Algorithms Library) to the [julia][2] language. It
serves as the supporting library for the CGAL.jl package (not yet published).

[CGAL][1] is a powerful easily-accessible C++ library that aims to provide
algorihtms in computational geometry (hence the name) with emphasis on
reliability and efficiency while still providing robust results.

# TODO

- [ ] Type Parametrization
- [ ] Global Functions
- [ ] Iterators
- [ ] Circulators
- [ ] Other packages, such as
  - [ ] Convex Hulls
  - [ ] Voronoi Delaunay
  - [ ] ...

# Building

The project can be built using the `build_tarballs.jl` [BinaryBuilder][3] script
under `.github/scripts`. This is also used in CI and for publishing artifacts on
release. It can also be built manually, albeit discouraged since setting up
the required dependencies may be an arduous task.

## Using `build_tarballs.jl` (recommended)

You're only required to have `julia>=1.0` installed. Once that requirement is
met, just run:

```sh
$ julia .github/scripts/build_tarballs.jl [optional,list,of,comma,separated,triplets]
```

You can provide a `--help` argument to get more information on `BinaryBuilder`'s
build script options. Check out [`BinaryBuilder.jl`][3] for more information.

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

- [`CMake`][4]
- [`CGAL==4.14.1`][5]
  * [`Boost==1.71`][6]
  * [`GMP`][7]
  * [`MPFR`][8]
- [`Julia>=1.0`][9]
- [`JlCxx==0.5.3`][10]

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

# Related Projects

- [cgal-swig-bindings][11] - CGAL bindings using SWIG
- [PYGAL - Python Geometric Algorithms Library][12] - CGAL python bindings using
  pybind11

[1]:  https://github.com/CGAL/cgal
[2]:  https://github.com/julialang/julia
[3]:  https://github.com/JuliaInterop/BinaryBuilder.jl
[4]:  https://github.com/Kitware/CMake/releases?after=3.13.2
[5]:  https://github.com/CGAL/cgal/releases/tag/releases%2FCGAL-4.13
[6]:  https://www.boost.org/users/history/version_1_69_0.html
[7]:  https://gmplib.org
[8]:  https://www.mpfr.org/mpfr-4.0.2
[9]:  https://github.com/julialang/julia/releases/tag/v1.0.5
[10]: https://github.com/JuliaInterop/libcxxwrap-julia/releases/tag/v0.5.3
[11]: https://github.com/CGAL/cgal-swig-bindings
[12]: https://github.com/wolfv/pygal
