# Note that this script can accept some limited command-line arguments, run
# `julia build_tarballs.jl --help` to see a usage message.
using BinaryBuilder

const name = "libcgal-julia"

version = v"0.99.0"
const matches = match(r"refs/tags/(.*)", get(ENV, "GITHUB_REF", ""))
if matches !== nothing
    try
        global version = VersionNumber(first(matches.captures))
    catch e
        @warn e.msg
    end
end
@info "$name v$version"

# Collection of sources required to build CGAL
const sources = [
    "."
]

# Dependencies that must be installed before this package can be built
dependencies = [
    # for CGAL
    "https://github.com/benlorenz/boostBuilder/releases/download/v1.69.0/build_boost.v1.69.0.jl",
    "https://github.com/JuliaPackaging/Yggdrasil/releases/download/GMP-v6.1.2-1/build_GMP.v6.1.2.jl",
    "https://github.com/JuliaPackaging/Yggdrasil/releases/download/MPFR-v4.0.2-1/build_MPFR.v4.0.2.jl",
    # for libcgal-julia
    "https://github.com/rgcv/CGALBuilder/releases/download/v4.14.1-1/build_CGAL.v4.14.1.jl",
    "https://github.com/JuliaPackaging/JuliaBuilder/releases/download/v1.0.0-2/build_Julia.v1.0.0.jl",
    "https://github.com/JuliaInterop/libcxxwrap-julia/releases/download/v0.5.3/build_libcxxwrap-julia-1.0.v0.5.3.jl"
]

# Bash recipe for building across all platforms
const script = raw"""
## pre-build setup
# exit on error
set -eu
# HACK: cmake v3.11 can't properly find Boost beyond 1.67.. here, we install a
# version of cmake (3.13.0) that recognizes Boost at least up to v1.69
apk del cmake
apk add cmake --repository http://dl-cdn.alpinelinux.org/alpine/v3.9/main

# check c++ standard reported by the compiler
# CGAL uses CMake's try_run to check if it needs to link with Boost.Thread
# depending on the c++ standard supported by the compiler. From c++11 onwards,
# CGAL doesn't require Boost.Thread
__need_boost_thread=1
__cplusplus=$($CXX -x c++ -dM -E - </dev/null | grep __cplusplus | grep -o '[0-9]*')
[ $__cplusplus -ge 201103 ] && __need_boost_thread=0


## configure build
mkdir -p "$WORKSPACE/srcdir/build" && cd "$WORKSPACE/srcdir/build"

CMAKE_FLAGS=(
  ## cmake specific
  -DCMAKE_TOOLCHAIN_FILE="/opt/$target/$target.toolchain"
  -DCMAKE_BUILD_TYPE=Release
  -DCMAKE_CXX_FLAGS="-march=x86-64"
  -DCMAKE_FIND_ROOT_PATH="$prefix"
  -DCMAKE_INSTALL_PREFIX="$prefix"
  # try_run doesn't like cross-compilation: this is required
  -DCGAL_test_cpp_version_RUN_RES=$__need_boost_thread
  -DCGAL_test_cpp_version_RUN_RES__TRYRUN_OUTPUT=$__cplusplus
  # tell libcxxwrap-julia where julia is
  -DJulia_PREFIX="$prefix"
)

cmake ${CMAKE_FLAGS[@]} ../

## and away we go..
VERBOSE=ON cmake --build . --config Release --target install
"""

# These are the platforms we will build for by default, unless further
# platforms are passed in on the command line
_abis( ::Type{<:Platform}) = (:gcc7,   :gcc8)
_archs(::Type{<:Platform}) = (:x86_64, :i686)
_archs(::Type{Linux})      = (:x86_64,)
platforms = Platform[]
for p in (Linux, Windows)
    for arch in _archs(p)
        for abi in _abis(p)
            push!(platforms, p(arch; compiler_abi=CompilerABI(abi, :cxx11)))
        end
    end
end
push!(platforms, MacOS(:x86_64))

# The products that we will ensure are always built
products(prefix) = [
    LibraryProduct(prefix, "libcgal_julia", :libcgal_julia),
]

# Build the tarballs, and possibly a `build.jl` as well.
build_tarballs(ARGS, name, version, sources, script, platforms, products, dependencies)
