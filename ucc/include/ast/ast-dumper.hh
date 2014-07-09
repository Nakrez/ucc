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

#ifndef UCC_AST_AST_DUMPER_HH
# define UCC_AST_AST_DUMPER_HH

# include <ostream>

# include <ucmp/misc/indent.hh>
# include <ucmp/misc/color.hh>

# include <ast/default-visitor.hh>

namespace ucc
{
    namespace ast
    {
        class AstDumper : public DefaultConstVisitor
        {
            public:
                using DefaultConstVisitor::operator();

                AstDumper(std::ostream& ostr);
                virtual ~AstDumper();

                template <class T>
                void dump_list(T& list)
                {
                    auto it = list.list_get().cbegin();
                    auto begin = list.list_get().cbegin();
                    auto end = list.list_get().cend();

                    for (; it != end; ++it)
                    {
                        if (it != begin)
                            ostr_ << ucmp::misc::iendl;

                        (*it)->accept(*this);
                    }
                }

                virtual void operator()(const AstList& ast) override;
                virtual void operator()(const DeclList& ast) override;
                virtual void operator()(const ExprList& ast) override;
                virtual void operator()(const FieldList& ast) override;
                virtual void operator()(const EnumExprList& ast) override;

                virtual void operator()(const VarDecl& ast) override;
                virtual void operator()(const FunctionDecl& ast) override;
                virtual void operator()(const TypeDecl& ast) override;

                virtual void operator()(const CompoundStmt& ast) override;
                virtual void operator()(const ReturnStmt& ast) override;
                virtual void operator()(const WhileStmt& ast) override;
                virtual void operator()(const BreakStmt& ast) override;
                virtual void operator()(const ContinueStmt& ast) override;

                virtual void operator()(const IntExpr& ast) override;
                virtual void operator()(const VarExpr& ast) override;
                virtual void operator()(const SubscriptExpr& ast) override;
                virtual void operator()(const AssignExpr& ast) override;
                virtual void operator()(const CallExpr& ast) override;
                virtual void operator()(const ConditionalExpr& ast) override;
                virtual void operator()(const OpExpr& ast) override;
                virtual void operator()(const UnaryExpr& ast) override;
                virtual void operator()(const CastExpr& ast) override;
                virtual void operator()(const ImplicitCastExpr& ast) override;

            protected:
                std::ostream& ostr_;
        };
    }
} // namespace ucc

#endif /* !UCC_AST_AST_DUMPER_HH */
