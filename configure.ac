AC_PREREQ([2.50])
AC_COPYRIGHT([Copyright Paul Campbell 2012])
AC_REVISION([$Revision: 1.0 $])
AC_INIT(ccload, 1.0, paul@taniwha.com)
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE(ccload, 1.0)

AC_CHECK_FUNCS([memset])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([termios.h])
AC_CHECK_HEADERS([unistd.h])
AC_C_CONST
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_LSTAT
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_STAT
AC_HEADER_DIRENT
AC_HEADER_STDBOOL
AC_HEADER_STDC
AC_PROG_CC
AC_PROG_CXX

AC_ARG_WITH([qt-libs], [AC_HELP_STRING([--with-qt-libs=DIR],
            [Path to the QT libraries])],
            [LDFLAGS="${LDFLAGS} -L${withval} -L${withval}"])

    PKG_CHECK_MODULES(QT4, QtGui >= 4.0.1)

    QT4_INCLUDE_DIR=$($PKG_CONFIG --variable=includedir QtGui)
    EXTRA_QT4_INCLUDE_DIR="$QT4_INCLUDE_DIR/Qt"
    AC_CHECK_FILE([$QT4_INCLUDE_DIR/QWidget],
                  AC_MSG_NOTICE([No extra QT4_INCLUDE_DIR needed]),

                  AC_CHECK_FILE([$EXTRA_QT4_INCLUDE_DIR/QWidget],
                        QT4_CFLAGS="$QT4_CFLAGS -I$EXTRA_QT4_INCLUDE_DIR",
                        AC_MSG_WARN([QWidget not found])))
    AC_MSG_NOTICE([Set QT4_CFLAGS... $QT4_CFLAGS])
    AC_CHECK_PROG(MOC, [moc], [moc])

    AC_SUBST(QT4_CFLAGS)
    AC_SUBST(QT4_LIBS)

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
