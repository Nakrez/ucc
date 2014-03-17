AM_CPPFLAGS = -I${top_srcdir}/ucc/include -I${top_srcdir}/lib/command/include \
			  -I${top_srcdir}/ucc/src -I${top_srcdir}/lib

bin_PROGRAMS = ucc
ucc_SOURCES = src/main.cc \
			  src/ucc.cc \
			  src/parse/c-parser.yy \
			  src/parse/driver.cc \
			  src/parse/c-lexer.ll \
			  src/parse/command.cc \
			  src/ast/ast.cc \
			  src/ast/decl.cc

ucc_LDADD = ${abs_top_builddir}/lib/command/libcommand.la
