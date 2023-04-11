################################################################################ 
# preamble
################################################################################ 

define(LIBMD407_COPYRIGHT,[[
Copyright (C) 2023  Albin Ahlbäck

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
]])
define(LIBMD407_COPYRIGHT_C,[[/*
Copyright (C) 2023  Albin Ahlbäck

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/]])

AC_COPYRIGHT(LIBMD407_COPYRIGHT)
AH_TOP(LIBMD407_COPYRIGHT_C)

AC_PREREQ(2.69)

define(LIBMD407_VERSION,[0.0.1-dev])

AC_INIT(LIBMD407, LIBMD407_VERSION, [https://github.com/albinahlback/libmd407/issues/], libmd407)
AC_LANG(C)

# Make sure that we are in the right directory
AC_CONFIG_SRCDIR(md407-ram.x)

################################################################################ 
# build system
################################################################################ 

# Get system triplet
AC_CANONICAL_HOST

################################################################################ 
# configure headers
################################################################################ 

# AC_CONFIG_HEADERS(src/flint-config.h:src/config.h.in)

################################################################################ 
# features
################################################################################ 

AC_ARG_ENABLE(debug,
[AS_HELP_STRING([--enable-debug],[Enable debugging [default=yes]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-debug. Need yes or no.])
    ;;
esac],
enable_debug="yes")

################################################################################ 
# programs
################################################################################ 

AC_PROG_CC

AC_PROG_MKDIR_P

################################################################################ 
# environment variables
################################################################################ 

AC_ARG_VAR(ABI, [Desired ABI])

################################################################################ 
# check programs and system
################################################################################ 

AC_SUBST(WL,$wl)

################################################################################ 
# check headers
################################################################################ 

# Mandatory headers
AC_CHECK_HEADERS([stdarg.h stdio.h stdlib.h stdint.h string.h math.h float.h errno.h gmp.h mpfr.h],,
                 AC_MSG_ERROR([Could not find a mandatory header!]))

################################################################################ 
# CFLAGS
################################################################################ 

CFLAGS="-O0 -Wall -Wextra -mthumb -march=armv6-m -mno-unaligned-access -mfloat-abi=soft -std=gnu17 -D SIMULATOR"
LIBS="-lgcc -lc_nano"
LDFLAGS="-Tmd407-ram.x -nostartfiles"

if test "$enable_debug" = "yes";
then
    CFLAGS="-g $CFLAGS"
fi

CPPFLAGS="-I./src $CPPFLAGS"

################################################################################ 
# substitutions and definitions
################################################################################ 

if test "$with_ntl" = "yes";
then
    AC_SUBST(WANT_NTL,1)
else
    AC_SUBST(WANT_NTL,0)
fi

if test "$with_blas" = "yes";
then
    AC_DEFINE(FLINT_USES_BLAS,1,[Define to enable BLAS.])
fi

################################################################################ 
# epilog
################################################################################ 

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
