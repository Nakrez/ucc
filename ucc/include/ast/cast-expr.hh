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

#ifndef UCC_AST_CAST_EXPR_HH
# define UCC_AST_CAST_EXPR_HH

# include <ast/ty.hh>
# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        /// Represent a cast in the ast
        class CastExpr : public Expr
        {
            public:
                /// \brief  Constructor
                /// \param  ty      The type node
                /// \param  expr    The expression casted
                CastExpr(const ucmp::misc::location& loc,
                         Ty* ty,
                         Expr* expr);

                /// Destructor
                virtual ~CastExpr();

                /// Return the Ty held by CastExpr
                const Ty* ty_get() const
                {
                    return ty_;
                }

                /// Return the Ty held by CastExpr
                Ty* ty_get()
                {
                    return ty_;
                }

                /// Return the Expr held by the CastExpr
                const Expr* expr_get() const
                {
                    return expr_;
                }

                /// Return the Expr held by the CastExpr
                Expr* expr_get()
                {
                    return expr_;
                }

                virtual void accept(Visitor& v) override
                {
                    v(*this);
                }

                virtual void accept(ConstVisitor& v) const override
                {
                    v(*this);
                }

            protected:
                Ty* ty_;
                Expr* expr_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_CAST_EXPR_HH */
