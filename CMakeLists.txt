project(CGAL-julia)
cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

## requirements
find_package(CGAL REQUIRED COMPONENTS Core)
include(${CGAL_USE_FILE})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Release mode with g++: using -fno-strict-aliasing flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")
  endif()
endif()

find_package(JlCxx)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

include_directories(${CGAL_INCLUDE_DIRS} ${JULIA_INCLUDE_DIRS})
include_directories(include)
set(CGAL_JLCXX_SOURCES
  src/origin.cpp
  src/enum.cpp
  src/kernel.cpp
  src/global_functions.cpp
  src/cgal_julia.cpp
)

add_library(cgal_julia SHARED ${CGAL_JLCXX_SOURCES})
target_link_libraries(cgal_julia JlCxx::cxxwrap_julia ${CGAL_LIBRARIES})
install(TARGETS
  cgal_julia
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib)
