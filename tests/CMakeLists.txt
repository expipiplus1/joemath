add_subdirectory( speed_test )

enable_testing()

#
# Testing
#
add_subdirectory( googletest EXCLUDE_FROM_ALL )

add_executable( joemath_tester EXCLUDE_FROM_ALL scalar.cpp vector.cpp vector_instantiation.cpp matrix.cpp )
add_dependencies( joemath_tester googletest )

add_executable( joemath_regression_tester EXCLUDE_FROM_ALL regression/regression.cpp
                                                           regression/test_data.hpp
                                                           regression/scalar.cpp 
                                                           regression/vector.cpp )
add_dependencies( joemath_regression_tester googletest )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${joemath_CXX_FLAGS}" )

include_directories( googletest/include )
include_directories( googletest )

#find_library( googletest_gtest      gtest      HINTS ${binary_dir} NO_DEFAULT_PATH )
#find_library( googletest_gtest_main gtest_main HINTS ${binary_dir} NO_DEFAULT_PATH )

target_link_libraries( joemath_tester            gtest gtest_main )
target_link_libraries( joemath_regression_tester gtest )

add_custom_target( check_joemath
                   COMMAND ${CMAKE_CTEST_COMMAND}
                   DEPENDS joemath_tester joemath_regression_tester)

#
# The code for discovering tests is from the compiz_discover_tests branch of
# Compiz
#

add_executable( joemath_discover_gtest_tests EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/joemath_discover_gtest_tests.cpp)

set_target_properties( joemath_discover_gtest_tests PROPERTIES
                       RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/joemath_gtest)

# Create target to discover tests
function( joemath_discover_tests EXECUTABLE )
    add_dependencies( ${EXECUTABLE} joemath_discover_gtest_tests )

    add_custom_command( TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE} --gtest_list_tests | ${CMAKE_BINARY_DIR}/joemath_gtest/joemath_discover_gtest_tests ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE} ${ARGN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Discovering Tests in ${EXECUTABLE}"
        DEPENDS
        VERBATIM )
endfunction()

joemath_discover_tests( joemath_tester "--gtest_repeat=1000" )
joemath_discover_tests( joemath_regression_tester ${CMAKE_SOURCE_DIR}/regression_test_data.txt )

