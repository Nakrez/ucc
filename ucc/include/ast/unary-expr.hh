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

#ifndef UCC_AST_UNARY_EXPR_HH
# define UCC_AST_UNARY_EXPR_HH

# include <string>

# include <ast/expr.hh>
# include <ast/type-builder.hh>

namespace ucc
{
    namespace ast
    {
        class UnaryExpr : public Expr, public TypeBuilder
        {
            public:
                enum UnaryOp
                {
                    BAND,
                    DEREF,
                    PLUS,
                    MINUS,
                    TILDE,
                    BANG,
                    PRE_INCR,
                    PRE_DECR,
                    POST_INCR,
                    POST_DECR,
                };

                UnaryExpr(const ucmp::misc::location& loc,
                          UnaryOp op,
                          Expr* expr);
                virtual ~UnaryExpr();

                UnaryOp op_get() const;

                std::string op_to_str() const;

                const Expr* expr_get() const;
                Expr* expr_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* expr_;
                UnaryOp op_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_UNARY_EXPR_HH */
