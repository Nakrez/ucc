AM_CPPFLAGS = -Iinclude -I../lib/command/include \
			  -Isrc -I../lib/misc/include \
			  -I${top_srcdir}/include

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
			  src/ast/array-ty.cc \
			  src/ast/function-ty.cc \
			  src/ast/ptr-ty.cc \
			  src/ast/record-ty.cc \
			  src/ast/enum-ty.cc \
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
			  src/ast/cast-expr.cc \
			  src/ast/implicit-cast-expr.cc \
			  src/ast/sizeof-expr.cc \
			  src/ast/init-list-expr.cc \
			  src/ast/type-builder.cc \
			  src/ast/type-user.cc \
			  src/ast/pretty-printer.cc \
			  src/ast/ast-dumper.cc \
			  src/ast/command.cc \
			  src/bind/binder.cc \
			  src/bind/command.cc \
			  src/type/floating-point.cc \
			  src/type/signed-integer.cc \
			  src/type/unsigned-integer.cc \
			  src/type/const.cc \
			  src/type/ptr.cc \
			  src/type/record.cc \
			  src/type/array.cc \
			  src/type/function.cc \
			  src/type/type.cc \
			  src/type/type-checker.cc \
			  src/type/command.cc \
			  src/analysis/uninitialized-variables.cc \
			  src/analysis/command.cc \
			  src/ir/command.cc \
			  src/gen/generator.cc \
			  src/gen/command.cc \
			  src/command.cc \
			  src/main.cc \
			  src/ucc.cc

ucc_LDADD = ../lib/command/libcommand.la \
			${top_builddir}/libucmp.la
