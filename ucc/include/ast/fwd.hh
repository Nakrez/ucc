/*
Copyright (C) 2014 Baptiste Covolato <b.covolato@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef UCC_AST_FWD_HH
# define UCC_AST_FWD_HH

namespace ucc
{
    namespace ast
    {
        class Ast;

        template<class T>
        class AnyList;

        class Decl;
        class DeclSpecifier;
        class Declarator;
        class VarDecl;
        class FunctionDecl;
        class TypeDecl;
        class FieldDecl;
        class RecordDecl;
        class EnumExprDecl;
        class EnumDecl;

        class Type;
        class NamedType;
        class ArrayType;
        class FunctionType;
        class PtrType;
        class RecordType;
        class EnumType;

        class Stmt;
        class CompoundStmt;
        class ReturnStmt;
        class WhileStmt;
        class DoWhileStmt;
        class LabelStmt;
        class GotoStmt;
        class BreakStmt;
        class ContinueStmt;
        class IfStmt;
        class SwitchStmt;
        class CaseStmt;
        class DefaultStmt;
        class ForStmt;

        class Expr;
        class IntExpr;
        class FloatExpr;
        class StringExpr;
        class VarExpr;
        class SubscriptExpr;
        class CallExpr;
        class AssignExpr;
        class ConditionalExpr;
        class OpExpr;
        class UnaryExpr;
        class MemberExpr;
        class EnumExpr;
        class CastExpr;
        class SizeofExpr;
        class InitListExpr;

        typedef AnyList<Ast> AstList;
        typedef AnyList<Decl> DeclList;
        typedef AnyList<Stmt> StmtList;
        typedef AnyList<Expr> ExprList;
        typedef AnyList<FieldDecl> FieldList;
        typedef AnyList<EnumExprDecl> EnumExprList;
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FWD_HH */
