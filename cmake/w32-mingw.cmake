# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)
 
# which compilers to use for C and C++
SET(CMAKE_C_COMPILER x86_64-pc-mingw32-gcc)
SET(CMAKE_CXX_COMPILER x86_64-pc-mingw32-g++)
SET(CMAKE_RC_COMPILER x86_64-pc-mingw32-windres)
 
# here is the target environment located
#if(WIN32)
#    SET(CMAKE_FIND_ROOT_PATH /MinGW/x86_64-w64-mingw32)
#else()
    set(CMAKE_FIND_ROOT_PATH /usr/mingw/x86_64-pc-mingw32)
#endif()
 
# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)