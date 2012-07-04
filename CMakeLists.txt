#--------------------------------------------------------------------
# CMakeLists.txt for joemath
# Adapted from glfw (http://glfw.org)
#--------------------------------------------------------------------

project(joemath)
cmake_minimum_required(VERSION 2.8)

include_directories(include)

set(joemath_SOURCES   ${joemath_SOURCE_DIR}/include/joemath/scalar.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/inl/scalar-inl.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/matrix.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/matrix_traits.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/inl/matrix-inl.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/joemath.hpp)

#--------------------------------------------------------------------
# Create shared configuration header
#--------------------------------------------------------------------

configure_file(${joemath_SOURCE_DIR}/libjoemath.pc.cmake 
               ${joemath_BINARY_DIR}/libjoemath.pc @ONLY)

set( CXX11_FLAGS "--std=c++11" )
#set( CXX11_FLAGS "--stdlib=libc++ --std=c++11" )

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]") 
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
else()
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W ${CXX11_FLAGS} -O3 -ffast-math -fomit-frame-pointer -finline-functions")
endif()

add_custom_target(JoeMath joemath_SOURCES ${joemath_SOURCES})

#--------------------------------------------------------------------
# Add example and test programs
#--------------------------------------------------------------------
add_subdirectory(tests)

#--------------------------------------------------------------------
# Install standard files 
#--------------------------------------------------------------------

install(DIRECTORY include/joemath DESTINATION include 
        FILES_MATCHING REGEX "(.*\\.hpp$|.*\\.inl$)")

install(FILES license.txt readme.txt 
        DESTINATION share/doc/joemath/)

#--------------------------------------------------------------------
# Uninstall operation
#--------------------------------------------------------------------
if( NOT TARGET uninstall )
    configure_file(${joemath_SOURCE_DIR}/cmake_uninstall.cmake.in
                   ${joemath_BINARY_DIR}/cmake_uninstall.cmake IMMEDIATE @ONLY)

    add_custom_target(uninstall
                      ${CMAKE_COMMAND} -P
                      ${joemath_BINARY_DIR}/cmake_uninstall.cmake)
endif()

