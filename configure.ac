dnl NOTE: This is only a minimal configure script.

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

AC_ARG_ENABLE(simulation,
[AS_HELP_STRING([--enable-simulation],[Enable simulation [default=yes]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-simulation. Need yes or no.])
    ;;
esac],
enable_simulation="yes")

################################################################################ 
# programs
################################################################################ 

AC_PROG_MKDIR_P

################################################################################ 
# check programs and system
################################################################################ 

# FIXME: Make proper check with AC_PROG_CC
AC_CHECK_PROG([CC], $host-gcc, $host-gcc, error)
if test "$ac_cv_prog_CC" = "error";
then
    AC_MSG_ERROR([Could not find gcc for the host. Did you specify the correct host?])
fi

AC_CHECK_PROG([AR], $host-ar, $host-ar, error)
if test "$ac_cv_prog_AR" = "error";
then
    AC_MSG_ERROR([Could not find ar for the host. Did you specify the correct host?])
fi

AC_CHECK_PROG([OBJCOPY], $host-objcopy, $host-objcopy, error)
if test "$ac_cv_prog_OBJCOPY" = "error";
then
    AC_MSG_ERROR([Could not find objcopy for the host. Did you specify the correct host?])
fi

################################################################################ 
# CFLAGS
################################################################################ 

AC_ARG_VAR([CFLAGS], [C compiler flags])
AC_ARG_VAR([LDFLAGS], [linker flags, e.g. -L<lib dir> if you have libraries in a nonstandard directory <lib dir>])
AC_ARG_VAR([LIBS], [libraries to pass to the linker, e.g. -l<library>])
AC_ARG_VAR([CPPFLAGS], [(Objective) C/C++ preprocessor flags, e.g. -I<include dir> if you have headers in a nonstandard directory <include dir>])

# Default values
if test -z "$CFLAGS";
then
    CFLAGS="-O0 -Wall -Wextra -mthumb -march=armv6-m -mno-unaligned-access -mfloat-abi=soft -std=gnu17"
fi

if test -z "$LDFLAGS";
then
    LDFLAGS="-Tmd407-ram.x"
fi

if test -z "$LIBS";
then
    LIBS="-lgcc -lc_nano -nostartfiles"
fi

CPPFLAGS="-I./src $CPPFLAGS"

# Options
if test "$enable_debug" = "yes";
then
    CFLAGS="-g $CFLAGS"
fi

if test "$enable_simulation" = "yes";
then
    CFLAGS="-D SIMULATOR"
fi

################################################################################ 
# epilog
################################################################################ 

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
