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

#ifndef UCC_AST_CONDITIONAL_EXPR_HH
# define UCC_AST_CONDITIONAL_EXPR_HH

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class ConditionalExpr : public Expr
        {
            public:
                ConditionalExpr(const ucc::parse::location& loc,
                                Expr* cond,
                                Expr* true_expr,
                                Expr* false_expr);
                virtual ~ConditionalExpr();

                const Expr* cond_get() const;
                Expr* cond_get();

                const Expr* true_expr_get() const;
                Expr* true_expr_get();

                const Expr* false_expr_get() const;
                Expr* false_expr_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* cond_;
                Expr* true_;
                Expr* false_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_CONDITIONAL_EXPR_HH */
