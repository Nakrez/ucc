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

#ifndef UCC_AST_VISITOR_HH
# define UCC_AST_VISITOR_HH

# include <misc/constness.hh>

# include <ast/fwd.hh>

namespace ucc
{
    namespace ast
    {
        template <template <typename> class Const>
        class GenVisitor
        {
            public:
                GenVisitor() = default;
                virtual ~GenVisitor() = default;

                virtual void operator()(typename Const<Ast>::type& ast);

                virtual void operator()(typename Const<AstList>::type& ast) = 0;
                virtual void operator()(typename Const<DeclList>::type& ast) = 0;
                virtual void operator()(typename Const<ExprList>::type& ast) = 0;
                virtual void operator()(typename Const<FieldList>::type& ast) = 0;
                virtual void operator()(typename Const<EnumExprList>::type& ast) = 0;

                virtual void operator()(typename Const<Decl>::type& ast) = 0;

                virtual void operator()(typename Const<Declarator>::type& ast) = 0;
                virtual void operator()(typename Const<VarDecl>::type& ast) = 0;
                virtual void operator()(typename Const<FunctionDecl>::type& ast) = 0;
                virtual void operator()(typename Const<TypeDecl>::type& ast) = 0;
                virtual void operator()(typename Const<FieldDecl>::type& ast) = 0;
                virtual void operator()(typename Const<RecordDecl>::type& ast) = 0;
                virtual void operator()(typename Const<EnumExprDecl>::type& ast) = 0;
                virtual void operator()(typename Const<EnumDecl>::type& ast) = 0;

                virtual void operator()(typename Const<Ty>::type& ast) = 0;

                virtual void operator()(typename Const<NamedTy>::type& ast) = 0;
                virtual void operator()(typename Const<ArrayTy>::type& ast) = 0;
                virtual void
                operator()(typename Const<FunctionTy>::type& ast) = 0;
                virtual void operator()(typename Const<PtrTy>::type& ast) = 0;
                virtual void operator()(typename Const<RecordTy>::type& ast) = 0;
                virtual void operator()(typename Const<EnumTy>::type& ast) = 0;

                virtual void operator()(typename Const<Stmt>::type& ast) = 0;
                virtual void operator()(typename Const<CompoundStmt>::type& ast) = 0;
                virtual void operator()(typename Const<ReturnStmt>::type& ast) = 0;
                virtual void operator()(typename Const<WhileStmt>::type& ast) = 0;
                virtual void operator()(typename Const<DoWhileStmt>::type& ast) = 0;
                virtual void operator()(typename Const<LabelStmt>::type& ast) = 0;
                virtual void operator()(typename Const<GotoStmt>::type& ast) = 0;
                virtual void operator()(typename Const<BreakStmt>::type& ast) = 0;
                virtual void operator()(typename Const<ContinueStmt>::type& ast) = 0;
                virtual void operator()(typename Const<IfStmt>::type& ast) = 0;
                virtual void operator()(typename Const<SwitchStmt>::type& ast) = 0;
                virtual void operator()(typename Const<CaseStmt>::type& ast) = 0;
                virtual void operator()(typename Const<DefaultStmt>::type& ast) = 0;
                virtual void operator()(typename Const<ForStmt>::type& ast) = 0;

                virtual void operator()(typename Const<Expr>::type& ast) = 0;
                virtual void operator()(typename Const<IntExpr>::type& ast) = 0;
                virtual void operator()(typename Const<FloatExpr>::type& ast) = 0;
                virtual void operator()(typename Const<StringExpr>::type& ast) = 0;
                virtual void operator()(typename Const<VarExpr>::type& ast) = 0;
                virtual void operator()(typename Const<SubscriptExpr>::type& ast) = 0;
                virtual void operator()(typename Const<CallExpr>::type& ast) = 0;
                virtual void operator()(typename Const<AssignExpr>::type& ast) = 0;
                virtual void operator()(typename Const<ConditionalExpr>::type& ast) = 0;
                virtual void operator()(typename Const<OpExpr>::type& ast) = 0;
                virtual void operator()(typename Const<UnaryExpr>::type& ast) = 0;
                virtual void operator()(typename Const<MemberExpr>::type& ast) = 0;
                virtual void operator()(typename Const<EnumExpr>::type& ast) = 0;
                virtual void operator()(typename Const<CastExpr>::type& ast) = 0;
                virtual void operator()(typename Const<ImplicitCastExpr>::type& ast) = 0;
                virtual void operator()(typename Const<SizeofExpr>::type& ast) = 0;
                virtual void operator()(typename Const<InitListExpr>::type& ast) = 0;
        };

        typedef GenVisitor<ucmp::misc::const_type> ConstVisitor;
        typedef GenVisitor<ucmp::misc::nonconst_type> Visitor;
    } // namespace ast
} // namespace ucc

# include <ast/visitor.hxx>

#endif /* !UCC_AST_VISITOR_HH */
