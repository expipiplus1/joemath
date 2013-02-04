#
# CMakeLists.txt for joemath
# Adapted from glfw (http://glfw.org)
#
project( joemath )

cmake_minimum_required( VERSION 2.8 )

include_directories( ${joemath_SOURCE_DIR}/include )

set(joemath_SOURCES   ${joemath_SOURCE_DIR}/include/joemath/scalar.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/inl/scalar-inl.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/matrix.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/matrix_traits.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/inl/matrix-inl.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/types.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/joemath.hpp)

#
# Create shared configuration header
#

enable_testing()

configure_file( ${joemath_SOURCE_DIR}/libjoemath.pc.cmake
                ${joemath_BINARY_DIR}/libjoemath.pc @ONLY )

set( joemath_CXX_FLAGS         "-std=c++11 -Wall" CACHE STRING "joemath compiler flags" )
set( joemath_CXX_FLAGS_RELEASE "-std=c++11 -Wall -O4 -ffast-math -fomit-frame-pointer -finline-functions" CACHE STRING "joelang release compiler flags" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${joemath_CXX_FLAGS}" )

add_custom_target( joemath joemath_SOURCES ${joemath_SOURCES} )

#
# Add example and test programs
#
add_subdirectory( tests )

#
# Install files
#

install( DIRECTORY include/joemath DESTINATION include
         FILES_MATCHING REGEX "(.*\\.hpp$)" )

#
# Uninstall operation
#
if( NOT TARGET uninstall )
    configure_file(${joemath_SOURCE_DIR}/cmake_uninstall.cmake.in
                   ${joemath_BINARY_DIR}/cmake_uninstall.cmake IMMEDIATE @ONLY)

    add_custom_target(uninstall
                      ${CMAKE_COMMAND} -P
                      ${joemath_BINARY_DIR}/cmake_uninstall.cmake)
endif()

