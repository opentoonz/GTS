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
dnl FLTK_CPPFLAGS="`$FLTK_CONFIG --cxxflags` -fno-exceptions"
AC_SUBST(FLTK_CPPFLAGS, "`$FLTK_CONFIG --cxxflags`")
AC_SUBST(FLTK_LIBS, "`$FLTK_CONFIG --use-gl --ldflags`")

case "$host" in
    *-*-cygwin* | *-*-mingw32*)
        on_windows=true
        CFLAGS="$CFLAGS -D_WIN32"
        CXXFLAGS="$CXXFLAGS -D_WIN32"
    ;;
esac
AM_CONDITIONAL([WINDOWS], [test x$on_windows = xtrue])

AC_CONFIG_FILES([
                 Makefile
                 ])

AC_OUTPUT
