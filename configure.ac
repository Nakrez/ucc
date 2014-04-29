AC_PREREQ([2.69])

AC_INIT([ucc], [0.1], [b.covolato@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror subdir-objects color-tests])
AM_SILENT_RULES([yes])

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_LANG([C++])

AC_PROG_CXX
AM_PROG_AR
AC_PROG_YACC
AC_PROG_LEX

LT_INIT

# Doxygen

DX_INIT_DOXYGEN(ucc, doc/Doxyfile, doc/gen)
DX_DOXYGEN_FEATURE(ON)
DX_DOT_FEATURE(ON)
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(ON)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile ucpp/Makefile lib/Makefile
                 lib/command/Makefile lib/misc/Makefile ucc/Makefile
                 tests/Makefile
                 doc/Doxyfile])

AC_OUTPUT
