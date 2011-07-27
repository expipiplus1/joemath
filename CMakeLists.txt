#--------------------------------------------------------------------
# CMakeLists.txt for joemath
# Adapted from glfw (http://glfw.org)
#--------------------------------------------------------------------

project(joemath)
cmake_minimum_required(VERSION 2.8)

include_directories(include)

set(joemath_SOURCES   ${joemath_SOURCE_DIR}/src/random.cpp
                      ${joemath_SOURCE_DIR}/include/joemath/random.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/scalar.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/inl/scalar-inl.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/matrix.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/inl/matrix-inl.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/joemath.hpp)

#--------------------------------------------------------------------
# Create shared configuration header
#--------------------------------------------------------------------

OPTION( JOEMATH_SIMD "Enable SIMD support" ON )
OPTION( JOEMATH_VEC_ASSERTS "Enable vec-op asserts in debug" OFF )

configure_file(${joemath_SOURCE_DIR}/include/joemath/config.hpp.in 
               ${joemath_SOURCE_DIR}/include/joemath/config.hpp @ONLY)

configure_file(${joemath_SOURCE_DIR}/libjoemath.pc.cmake 
               ${joemath_BINARY_DIR}/libjoemath.pc @ONLY)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]") 
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -std=c++0x -g3 -O0 -ffast-math -fomit-frame-pointer -finline-functions")
endif()

add_library(libjoemathStatic    STATIC    ${joemath_SOURCES})
add_library(libjoemathShared    SHARED    ${joemath_SOURCES})

#--------------------------------------------------------------------
# Set up joemath on windows
#--------------------------------------------------------------------
if (WIN32)
   # set_target_properties(libjoemathShared PROPERTIES 
   #                         DEFINE_SYMBOL JOEMATH_BUILD_DLL
   #                         PREFIX ""
   #                         IMPORT_PREFIX ""
   #                         IMPORT_SUFFIX "dll.lib")
endif (WIN32)

set_target_properties(libjoemathStatic libjoemathShared PROPERTIES 
		      CLEAN_DIRECT_OUTPUT 1
		      OUTPUT_NAME joemath)

install(TARGETS libjoemathStatic libjoemathShared DESTINATION lib)
install(FILES ${joemath_BINARY_DIR}/libjoemath.pc DESTINATION lib/pkgconfig)
  
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

