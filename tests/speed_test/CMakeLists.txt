include_directories(${joemath_SOURCE_DIR}/include)

add_executable(speed_test   main.cpp
                            timer.hpp
                            timer.cpp) 

target_link_libraries(speed_test libjoemathStatic)

