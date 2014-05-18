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

#ifndef UCC_AST_DEFAULT_VISITOR_HH
# define UCC_AST_DEFAULT_VISITOR_HH

# include <cassert>

# include <ucmp/misc/constness.hh>

# include <ast/visitor.hh>
# include <ast/all.hh>

namespace ucc
{
    namespace ast
    {
        template <template <typename> class Const>
        class GenDefaultVisitor : public GenVisitor<Const>
        {
            public:
                using GenVisitor<Const>::operator();

                GenDefaultVisitor() = default;
                virtual ~GenDefaultVisitor() = default;

                virtual void operator()(typename Const<AstList>::type& ast);
                virtual void operator()(typename Const<DeclList>::type& ast);
                virtual void operator()(typename Const<ExprList>::type& ast);
                virtual void operator()(typename Const<FieldList>::type& ast);
                virtual void operator()(typename Const<EnumExprList>::type& ast);

                virtual void operator()(typename Const<Decl>::type& ast);

                virtual void operator()(typename Const<Declarator>::type& ast);
                virtual void operator()(typename Const<VarDecl>::type& ast);
                virtual void operator()(typename Const<FunctionDecl>::type& ast);
                virtual void operator()(typename Const<TypeDecl>::type& ast);
                virtual void operator()(typename Const<FieldDecl>::type& ast);
                virtual void operator()(typename Const<RecordDecl>::type& ast);
                virtual void operator()(typename Const<EnumExprDecl>::type& ast);
                virtual void operator()(typename Const<EnumDecl>::type& ast);

                virtual void operator()(typename Const<Ty>::type& ast);

                virtual void operator()(typename Const<NamedTy>::type& ast);
                virtual void operator()(typename Const<ArrayTy>::type& ast);
                virtual void
                operator()(typename Const<FunctionTy>::type& ast);
                virtual void operator()(typename Const<PtrTy>::type& ast);
                virtual void operator()(typename Const<RecordTy>::type& ast);
                virtual void operator()(typename Const<EnumTy>::type& ast);

                virtual void operator()(typename Const<Stmt>::type& ast);
                virtual void operator()(typename Const<CompoundStmt>::type& ast);
                virtual void operator()(typename Const<ReturnStmt>::type& ast);
                virtual void operator()(typename Const<WhileStmt>::type& ast);
                virtual void operator()(typename Const<DoWhileStmt>::type& ast);
                virtual void operator()(typename Const<LabelStmt>::type& ast);
                virtual void operator()(typename Const<GotoStmt>::type& ast);
                virtual void operator()(typename Const<BreakStmt>::type& ast);
                virtual void operator()(typename Const<ContinueStmt>::type& ast);
                virtual void operator()(typename Const<IfStmt>::type& ast);
                virtual void operator()(typename Const<SwitchStmt>::type& ast);
                virtual void operator()(typename Const<CaseStmt>::type& ast);
                virtual void operator()(typename Const<DefaultStmt>::type& ast);
                virtual void operator()(typename Const<ForStmt>::type& ast);

                virtual void operator()(typename Const<Expr>::type& ast);
                virtual void operator()(typename Const<IntExpr>::type& ast);
                virtual void operator()(typename Const<FloatExpr>::type& ast);
                virtual void operator()(typename Const<StringExpr>::type& ast);
                virtual void operator()(typename Const<VarExpr>::type& ast);
                virtual void operator()(typename Const<SubscriptExpr>::type& ast);
                virtual void operator()(typename Const<CallExpr>::type& ast);
                virtual void operator()(typename Const<AssignExpr>::type& ast);
                virtual void operator()(typename Const<ConditionalExpr>::type& ast);
                virtual void operator()(typename Const<OpExpr>::type& ast);
                virtual void operator()(typename Const<UnaryExpr>::type& ast);
                virtual void operator()(typename Const<MemberExpr>::type& ast);
                virtual void operator()(typename Const<EnumExpr>::type& ast);
                virtual void operator()(typename Const<CastExpr>::type& ast);
                virtual void operator()(typename Const<ImplicitCastExpr>::type& ast);
                virtual void operator()(typename Const<SizeofExpr>::type& ast);
                virtual void operator()(typename Const<InitListExpr>::type& ast);
        };

        typedef GenDefaultVisitor<ucmp::misc::const_type> DefaultConstVisitor;
        typedef GenDefaultVisitor<ucmp::misc::nonconst_type> DefaultVisitor;
    } // namespace ast
} // namespace ucc

# include <ast/default-visitor.hxx>

#endif /* !UCC_AST_DEFAULT_VISITOR_HH */
