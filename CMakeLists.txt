cmake_minimum_required(VERSION 3.1)

project(JlCGAL
        VERSION 0.16.0
        LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

find_package(CGAL 5.2 CONFIG REQUIRED COMPONENTS Core)

find_package(JlCxx 0.8 REQUIRED)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

set(JLCGAL_TARGETS cgal_julia_exact cgal_julia_inexact)
set(JLCGAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(JLCGAL_HEADERS
    ${JLCGAL_INCLUDE_DIR}/io.hpp
    ${JLCGAL_INCLUDE_DIR}/global_kernel_functions.hpp
    ${JLCGAL_INCLUDE_DIR}/kernel.hpp
    ${JLCGAL_INCLUDE_DIR}/kernel_conversion.hpp
    ${JLCGAL_INCLUDE_DIR}/polygon_2.hpp
    ${JLCGAL_INCLUDE_DIR}/triangulation.hpp
    ${JLCGAL_INCLUDE_DIR}/utils.hpp
    )
add_subdirectory(src) # let each directory take care of the sources

foreach(tgt IN ITEMS ${JLCGAL_TARGETS})
  add_library(${tgt} SHARED ${JLCGAL_SOURCES} ${JLCGAL_HEADERS})
  set_target_properties(${tgt} PROPERTIES
                        VERSION ${PROJECT_VERSION}
                        SOVERSION ${PROJECT_VERSION_MAJOR})
  target_link_libraries(${tgt}
                        JlCxx::cxxwrap_julia
                        CGAL::CGAL
                        CGAL::CGAL_Core)
  target_include_directories(${tgt} PRIVATE ${JLCGAL_INCLUDE_DIR})
  target_sources(${tgt} PRIVATE ${JLCGAL_SOURCES})
endforeach(tgt)

target_compile_definitions(cgal_julia_exact PRIVATE JLCGAL_EXACT_CONSTRUCTIONS)

install(TARGETS ${JLCGAL_TARGETS}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
