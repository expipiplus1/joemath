prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

Name: joemath
Description: Linear math library
Version: 0.0.1
URL: git://lon.eso.me.uk/joemath
Libs: -L${libdir} -ljoemath
Cflags: -I${includedir}
