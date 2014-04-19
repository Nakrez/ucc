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

#ifndef UCC_AST_OP_EXPR_HH
# define UCC_AST_OP_EXPR_HH

# include <string>

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class OpExpr : public Expr
        {
            public:
                enum Op
                {
                    OP_PLUS,
                    OP_MINUS,
                    OP_MUL,
                    OP_DIV,
                    OP_MOD,
                    OP_GT,
                    OP_GE,
                    OP_LT,
                    OP_LE,
                    OP_EQ,
                    OP_DIFF,
                    OP_LSHIFT,
                    OP_RSHIFT,
                    OP_BAND,
                    OP_XOR,
                    OP_BOR,
                    OP_AND,
                    OP_OR,
                    OP_COMA
                };

            public:
                OpExpr(const ucc::misc::location& loc,
                       Expr* lexpr,
                       Op op,
                       Expr* rexpr);
                virtual ~OpExpr();

                const Expr* lexpr_get() const;
                Expr* lexpr_get();

                const Expr* rexpr_get() const;
                Expr* rexpr_get();

                Op op_get() const;

                std::string op_to_str() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* lexpr_;
                Expr* rexpr_;
                Op op_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_OP_EXPR_HH */
