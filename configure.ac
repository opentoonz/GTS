AC_INIT([GTS], [2.3.8], [], [GTS], [https://github.com/opentoonz/GTS])

AM_INIT_AUTOMAKE([subdir-objects foreign])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CC_STDC
LT_INIT

PKG_CHECK_MODULES([TIFF], [libtiff-4])
AX_CHECK_GLU

AC_PATH_TOOL(FLTK_CONFIG, fltk-config, no)
if test "$FLTK_CONFIG" = "no"; then
    AC_MSG_ERROR(fltk-config is required)
fi
AC_SUBST(FLTK_CPPFLAGS, "`$FLTK_CONFIG --cxxflags`")
AC_SUBST(FLTK_LIBS, "`$FLTK_CONFIG --use-gl --ldflags`")

on_windows=no
case "$host" in
    *-*-cygwin* | *-*-mingw32*)
        on_windows=yes
        CFLAGS="$CFLAGS -D_WIN32"
        CXXFLAGS="$CXXFLAGS -D_WIN32"
    ;;
esac
AM_CONDITIONAL([WINDOWS], [test "$on_windows" = "yes"])

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

AC_DEFINE_UNQUOTED(CONFIGURATION_DATE, ["`date '+%Y-%m-%d'`"], [configuration date])

AC_CONFIG_FILES([
                 Makefile
                 ])

AC_OUTPUT

