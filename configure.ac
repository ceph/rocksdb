#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rockdb], [3.0])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_LANG_CPLUSPLUS
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_CHECK_LIB([snappy], [snappy_compress], [HAVE_LIBSNAPPY=yes], [AC_MSG_FAILURE([libsnappy not found])])
AC_CHECK_LIB([z], [gzread], [HAVE_LIBZ=yes], [AC_MSG_FAILURE([libz not found])])
AC_CHECK_LIB([bz2], [BZ2_bzCompressInit], [HAVE_LIBBZ2=yes], [AC_MSG_FAILURE([libbz2 not found])])
AC_CHECK_LIB([rt], [clock_gettime], [HAVE_LIBRT=yes], [AC_MSG_FAILURE([librt not found])])
AC_CHECK_LIB([tcmalloc], [malloc],  [HAVE_LIBTCMALLOC=yes],[AC_MSG_FAILURE([no tcmalloc found ])])

OLD_CXXFLAGS="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -std=c++11"

AC_COMPILE_IFELSE([AC_LANG_SOURCE([
#include <atomic>
int main() {}
])], [
     HAVE_ATOMIC=yes
   ],
   [
     HAVE_ATOMIC=no
   ])
AC_COMPILE_IFELSE([AC_LANG_SOURCE([
#include <gflags/gflags.h>
using namespace gflags;
int main() {}
])], [
     HAVE_GFLAGS_GFLAGS=yes
   ],
   [
     HAVE_GFLAGS_GFLAGS=no
   ])
AC_COMPILE_IFELSE([AC_LANG_SOURCE([
#include <gflags/gflags.h>
using namespace google;
int main() {}
])], [
     HAVE_GOOGLE_GFLAGS=yes
   ],
   [
     HAVE_GOOGLE_GFLAGS=no
   ])

AC_COMPILE_IFELSE([AC_LANG_SOURCE([
#include <fcntl.h>
      int main() {
        int fd = open("/dev/null", 0);
        fallocate(fd, 0, 0, 1024);
      }
])], [
     HAVE_FALLOCATE=yes
   ],
   [
     HAVE_FALLOCATE=no
   ])

AM_CONDITIONAL(WITH_TCMALLOC, [test x"$HAVE_LIBTCMALLOC" = "xyes"])
AM_CONDITIONAL(WITH_ATOMIC, [test x"$HAVE_ATOMIC" = "xyes"])
AM_CONDITIONAL(WITH_SNAPPY, [test x"$HAVE_LIBSNAPPY" = "xyes"])
AM_CONDITIONAL(WITH_Z, [test x"$HAVE_LIBZ" = "xyes" ])
AM_CONDITIONAL(WITH_BZ2, [test x"$HAVE_LIBBZ2" = "xyes"])
AM_CONDITIONAL(WITH_RT, [test x"$HAVE_LIBRT" = "xyes"])
AM_CONDITIONAL(WITH_GOOGLE_FLAGS, [test x"$HAVE_GFLAGS_GFLAGS" = "xyes"])
AM_CONDITIONAL(WITH_GFLAGS_FLAGS, [test x"$HAVE_GOOGLE_GFLAGS" = "xyes"])
AM_CONDITIONAL(WITH_FALLOCATE, [test x"$HAVE_FALLOCATE" = "xyes"])

AC_OUTPUT
