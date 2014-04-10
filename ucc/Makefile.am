AM_CPPFLAGS = -I${top_srcdir}/ucc/include -I${top_srcdir}/lib/command/include \
			  -I${top_srcdir}/ucc/src -I${top_srcdir}/lib/misc/include

bin_PROGRAMS = ucc
ucc_SOURCES = src/parse/c-parser.yy \
			  src/parse/driver.cc \
			  src/parse/c-lexer.ll \
			  src/parse/command.cc \
			  src/ast/ast.cc \
			  src/ast/decl.cc \
			  src/ast/decl-specifier.cc \
			  src/ast/declarator.cc \
			  src/ast/var-decl.cc \
			  src/ast/function-decl.cc \
			  src/ast/type-decl.cc \
			  src/ast/field-decl.cc \
			  src/ast/record-decl.cc \
			  src/ast/enum-expr-decl.cc \
			  src/ast/enum-decl.cc \
			  src/ast/type.cc \
			  src/ast/named-type.cc \
			  src/ast/array-type.cc \
			  src/ast/function-type.cc \
			  src/ast/ptr-type.cc \
			  src/ast/record-type.cc \
			  src/ast/stmt.cc \
			  src/ast/compound-stmt.cc \
			  src/ast/return-stmt.cc \
			  src/ast/while-stmt.cc \
			  src/ast/do-while-stmt.cc \
			  src/ast/label-stmt.cc \
			  src/ast/goto-stmt.cc \
			  src/ast/break-stmt.cc \
			  src/ast/continue-stmt.cc \
			  src/ast/if-stmt.cc \
			  src/ast/switch-stmt.cc \
			  src/ast/case-stmt.cc \
			  src/ast/default-stmt.cc \
			  src/ast/for-stmt.cc \
			  src/ast/expr.cc \
			  src/ast/int-expr.cc \
			  src/ast/float-expr.cc \
			  src/ast/string-expr.cc \
			  src/ast/var-expr.cc \
			  src/ast/subscript-expr.cc \
			  src/ast/call-expr.cc \
			  src/ast/assign-expr.cc \
			  src/ast/conditional-expr.cc \
			  src/ast/op-expr.cc \
			  src/ast/unary-expr.cc \
			  src/ast/member-expr.cc \
			  src/ast/enum-expr.cc \
			  src/ast/pretty-printer.cc \
			  src/ast/command.cc \
			  src/main.cc \
			  src/ucc.cc

ucc_LDADD = ${abs_top_builddir}/lib/command/libcommand.la \
			${abs_top_builddir}/lib/misc/libmisc.la
