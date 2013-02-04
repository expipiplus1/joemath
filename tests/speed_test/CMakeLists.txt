include_directories(${joemath_SOURCE_DIR}/include)

add_executable(speed_test main.cpp ${joemath_SOURCES})

set_target_properties(speed_test PROPERTIES COMPILE_FLAGS ${joemath_CXX_FLAGS})

