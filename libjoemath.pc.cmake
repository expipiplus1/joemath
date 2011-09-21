prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

Name: joemath
Description: Linear math library
Version: 0.0.1
URL: https://github.com/expipiplus1/joemath
Libs: -L${libdir} -ljoemath
Cflags: -I${includedir}
