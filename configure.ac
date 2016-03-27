AC_INIT([GTS], [2.3.0], [shimizu.toshihiro@gmail.com], [GTS], [https://github.com/opentoonz/GTS])

AM_INIT_AUTOMAKE([subdir-objects foreign])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CC
AC_PROG_CXX
LT_INIT

PKG_CHECK_MODULES([TIFF], [libtiff-4])
AX_CHECK_GLU

AC_PATH_PROG(FLTK_CONFIG, fltk-config, no)
if test "$FLTK_CONFIG" = "no"; then
    AC_MSG_ERROR(fltk-config is required)
fi
dnl FLTK_CXXFLAGS="`$FLTK_CONFIG --cxxflags` -fno-exceptions"
FLTK_CXXFLAGS="`$FLTK_CONFIG --cxxflags`"
FLTK_LIBS="`$FLTK_CONFIG --ldflags`"

AC_CONFIG_FILES([
                 Makefile
                 ])

AC_OUTPUT
