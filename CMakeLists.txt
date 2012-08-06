#
# CMakeLists.txt for joemath
# Adapted from glfw (http://glfw.org)
#
project( joemath )

cmake_minimum_required( VERSION 2.8 )

option( joemath_build_tests "Build the tests for JoeMath" OFF )

include_directories( ${joemath_SOURCE_DIR}/include )

set(joemath_SOURCES   ${joemath_SOURCE_DIR}/include/joemath/scalar.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/inl/scalar-inl.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/matrix.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/matrix_traits.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/inl/matrix-inl.hpp
                      ${joemath_SOURCE_DIR}/include/joemath/joemath.hpp)

#
# Create shared configuration header
#

configure_file( ${joemath_SOURCE_DIR}/libjoemath.pc.cmake 
                ${joemath_BINARY_DIR}/libjoemath.pc @ONLY )

set( joemath_CXX_FLAGS         "-std=c++0x -Wall" CACHE STRING "joemath compiler flags" )
set( joemath_CXX_FLAGS_RELEASE "-std=c++0x -Wall -O4 -ffast-math -fomit-frame-pointer -finline-functions" CACHE STRING "joelang release compiler flags" )

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
# Testing
#

if( joemath_build_tests )
    # Enable ExternalProject CMake module
    include(ExternalProject)

    # Set default ExternalProject root directory
    SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)
    # Add gtest
    ExternalProject_Add(
        googletest
        SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
        TIMEOUT 10
        # Force separate output paths for debug and release builds to allow easy
        # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
        CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
                   -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
                   -Dgtest_force_shared_crt=ON
        # Disable install step
        INSTALL_COMMAND ""
        # Wrap download, configure and build steps in a script to log output
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON)
    # Specify include dir
    ExternalProject_Get_Property(googletest source_dir)
    include_directories(${source_dir}/include)

    # C++ tests
    enable_testing()
    set( tests  tests/scalar.cpp
                tests/vector.cpp
                tests/vector_instantiation.cpp
                tests/matrix.cpp )
    add_executable( tester ${tests} )

    # Specify tester's link libraries
    ExternalProject_Get_Property(googletest binary_dir)
    #find_library( googletest_gtest gtest HINTS ${binary_dir} NO_DEFAULT_PATH )
    #find_library( googletest_gtest_main gtest_main HINTS ${binary_dir} NO_DEFAULT_PATH )
    add_library( gtest UNKNOWN IMPORTED )
    add_library( gtest_main UNKNOWN IMPORTED )
    set_target_properties( gtest PROPERTIES IMPORTED_LOCATION
                                            ${binary_dir}/libgtest.a )
    set_target_properties( gtest_main PROPERTIES IMPORTED_LOCATION
                                                 ${binary_dir}/libgtest_main.a )
    target_link_libraries( tester gtest gtest_main )

    # Create dependency of MainTest on googletest
    add_dependencies( tester googletest )

    macro(ADD_GOOGLE_TESTS executable)
      foreach ( source ${ARGN} )
        file(READ "${source}" contents)
        string(REGEX MATCHALL "TYPED_TEST *\\(([A-Za-z_0-9 ,]+)\\)" found_tests ${contents})
        foreach(hit ${found_tests})
          string(REGEX REPLACE ".*\\(([A-Za-z_0-9]+)[, ]*([A-Za-z_0-9]+) *\\).*" "\\1.\\2" test_name ${hit})
          message(STATUS ${test_name} )
          add_test(${test_name} ${executable} --gtest_repeat=1000 --gtest_filter=${test_name})
        endforeach(hit)
      endforeach()
    endmacro()

    # Add all tests found in the source code, calling the executable to run them
    # add_google_tests ( ${EXECUTABLE_OUTPUT_PATH}/tester ${tests})
    add_test( all_tests tester --gtest_repeat=1000 )
endif()

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

