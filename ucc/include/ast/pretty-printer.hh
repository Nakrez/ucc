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

#ifndef UCC_AST_PRETTY_PRINTER_HH
# define UCC_AST_PRETTY_PRINTER_HH

# include <ostream>

# include <ast/all.hh>
# include <ast/default-visitor.hh>

namespace ucc
{
    namespace ast
    {
        class PrettyPrinter : public DefaultConstVisitor
        {
            public:
                using DefaultConstVisitor::operator();

                PrettyPrinter(std::ostream& ostr);
                virtual ~PrettyPrinter();

                void activate_bindings();

                virtual void operator()(const AstList& ast);
                virtual void operator()(const DeclList& ast);
                virtual void operator()(const ExprList& ast);
                virtual void operator()(const FieldList& ast);
                virtual void operator()(const EnumExprList& ast);

                virtual void operator()(const VarDecl& ast);
                virtual void operator()(const TypeDecl& ast);
                virtual void operator()(const FunctionDecl& ast);
                virtual void operator()(const FieldDecl& ast);
                virtual void operator()(const RecordDecl& ast);
                virtual void operator()(const EnumExprDecl& ast);
                virtual void operator()(const EnumDecl& ast);

                virtual void operator()(const ArrayTy& ast);
                virtual void operator()(const NamedTy& ast);
                virtual void operator()(const PtrTy& ast);
                virtual void operator()(const RecordTy& ast);
                virtual void operator()(const EnumTy& ast);

                virtual void operator()(const CompoundStmt& ast);
                virtual void operator()(const ReturnStmt& ast);
                virtual void operator()(const WhileStmt& ast);
                virtual void operator()(const DoWhileStmt& ast);
                virtual void operator()(const LabelStmt& ast);
                virtual void operator()(const GotoStmt& ast);
                virtual void operator()(const BreakStmt& ast);
                virtual void operator()(const ContinueStmt& ast);
                virtual void operator()(const IfStmt& ast);
                virtual void operator()(const SwitchStmt& ast);
                virtual void operator()(const CaseStmt& ast);
                virtual void operator()(const DefaultStmt& ast);
                virtual void operator()(const ForStmt& ast);

                virtual void operator()(const IntExpr& ast);
                virtual void operator()(const FloatExpr& ast);
                virtual void operator()(const StringExpr& ast);
                virtual void operator()(const VarExpr& ast);
                virtual void operator()(const SubscriptExpr& ast);
                virtual void operator()(const CallExpr& ast);
                virtual void operator()(const AssignExpr& ast);
                virtual void operator()(const ConditionalExpr& ast);
                virtual void operator()(const OpExpr& ast);
                virtual void operator()(const UnaryExpr& ast);
                virtual void operator()(const MemberExpr& ast);
                virtual void operator()(const EnumExpr& ast);
                virtual void operator()(const CastExpr& ast);
                virtual void operator()(const ImplicitCastExpr& ast);
                virtual void operator()(const SizeofExpr& ast);
                virtual void operator()(const InitListExpr& ast);

            protected:
                bool print_fun_ptr(const Ty* ast,
                                   const ucmp::misc::Symbol& sym);
                bool print_array_ty(const Ty* ast,
                                    const ucmp::misc::Symbol& sym);

            protected:
                bool formals_;
                bool with_bindings_;
                std::ostream& ostr_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_PRETTY_PRINTER_HH */
