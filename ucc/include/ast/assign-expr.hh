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

#ifndef UCC_AST_ASSIGN_EXPR_HH
# define UCC_AST_ASSIGN_EXPR_HH

# include <string>

# include <ast/expr.hh>
# include <ast/op-expr.hh>

namespace ucc
{
    namespace ast
    {
        class AssignExpr : public Expr
        {
            public:
                enum AssignOp
                {
                    ASSIGN,
                    MUL_ASSIGN,
                    DIV_ASSIGN,
                    MOD_ASSIGN,
                    PLUS_ASSIGN,
                    MINUS_ASSIGN,
                    LSHIFT_ASSIGN,
                    RSHIFT_ASSIGN,
                    BAND_ASSIGN,
                    BXOR_ASSIGN,
                    BOR_ASSIGN
                };

            public:
                AssignExpr(const ucc::misc::location& loc,
                           Expr* lvalue,
                           AssignOp op,
                           Expr* rvalue);
                virtual ~AssignExpr();

                const Expr* lvalue_get() const
                {
                    return lvalue_;
                }

                Expr* lvalue_get()
                {
                    return lvalue_;
                }

                const Expr* rvalue_get() const
                {
                    return rvalue_;
                }

                Expr* rvalue_get()
                {
                    return rvalue_;
                }

                AssignOp op_get() const
                {
                    return op_;
                }

                void rvalue_set(Expr* e)
                {
                    rvalue_ = e;
                }

                std::string op_to_str() const;

                virtual void accept(Visitor& v) override
                {
                    v(*this);
                }

                virtual void accept(ConstVisitor& v) const override
                {
                    v(*this);
                }

            protected:
                Expr* lvalue_;
                Expr* rvalue_;
                AssignOp op_;
        };

        OpExpr::Op assign_op_to_op_expr(AssignExpr::AssignOp op);
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ASSIGN_EXPR_HH */
