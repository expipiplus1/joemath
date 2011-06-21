# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)
 
# which compilers to use for C and C++
SET(CMAKE_C_COMPILER i686-pc-mingw32-gcc)
SET(CMAKE_CXX_COMPILER i686-pc-mingw32-g++)
if(WIN32)
    SET(CMAKE_RC_COMPILER C:/mingw/bin/i686-pc-mingw32-windres)
else()
    SET(CMAKE_RC_COMPILER /usr/bin/i686-pc-mingw32-windres)
endif()
 
# here is the target environment located
if(WIN32)
    SET(CMAKE_FIND_ROOT_PATH C:/mingw/i686-pc-mingw32)
else()
    set(CMAKE_FIND_ROOT_PATH /usr/mingw/i686-pc-mingw32)
endif()
 
# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
