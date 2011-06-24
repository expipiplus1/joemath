# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Linux)
 
# which compilers to use for C and C++
SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)
 
# here is the target environment located
#set(CMAKE_FIND_ROOT_PATH /usr/i686-linux-gnu)
 
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -m32 -march=i686)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -m32 -march=i686)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
