AC_INIT([GTS], [2.5.1], [], [GTS], [https://github.com/opentoonz/GTS])

AM_INIT_AUTOMAKE([subdir-objects foreign])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CC_STDC
AC_GNU_SOURCE
LT_INIT

AC_CHECK_FUNCS([__secure_getenv secure_getenv])
AC_FUNC_STRERROR_R
PKG_CHECK_MODULES([TIFF], [libtiff-4])
AX_CHECK_GLU
PKG_CHECK_MODULES(GLEW, [glew])
AC_CHECK_LIB(pthread, pthread_create, [LIBS="$LIBS -pthread"])

AC_PATH_TOOL(FLTK_CONFIG, fltk-config, no)
if test "$FLTK_CONFIG" = "no"; then
    AC_MSG_ERROR(fltk-config is required)
fi
AC_SUBST(FLTK_CPPFLAGS, "`$FLTK_CONFIG --cxxflags`")
AC_SUBST(FLTK_LIBS, "`$FLTK_CONFIG --use-gl --ldflags`")

on_windows=no
on_macos=no
case "$host" in
    *cygwin* | *mingw*)
        on_windows=yes
        CFLAGS="$CFLAGS -D_WIN32"
        CXXFLAGS="$CXXFLAGS -D_WIN32"
    ;;
    *darwin*)
        on_macos=yes
        CFLAGS="$CFLAGS -D_MACOS"
        CXXFLAGS="$CXXFLAGS -D_MACOS"
    ;;
esac
AM_CONDITIONAL([WINDOWS], [test "$on_windows" = "yes"])
AM_CONDITIONAL([MACOS], [test "$on_macos" = "yes"])

if test "$on_windows" = "no"; then
    AC_CHECK_HEADERS([sane/sane.h], [], [AC_MSG_ERROR([SANE not found])])
    AC_PATH_TOOL(SANE_CONFIG, sane-config, no)
    if test "$SANE_CONFIG" = "no"; then
        AC_MSG_ERROR(sane-config is required)
    fi
    AC_SUBST(SANE_CFLAGS, `$SANE_CONFIG --cflags`)
    AC_SUBST(SANE_LDFLAGS, `$SANE_CONFIG --ldflags`)
    AC_SUBST(SANE_LIBS, `$SANE_CONFIG --libs`)
fi

if test "$on_macos" = "yes"; then
	AX_BOOST_BASE([], [], [AC_MSG_ERROR([Boost not found])])
	AX_BOOST_FILESYSTEM
fi

AC_DEFINE_UNQUOTED(CONFIGURATION_DATE, ["`date '+%Y-%m-%d'`"], [configuration date])

AC_CONFIG_FILES([
                 Makefile
                 ])

AC_OUTPUT

