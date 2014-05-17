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

#ifndef UCC_AST_ARRAY_TY_HH
# define UCC_AST_ARRAY_TY_HH

# include <ast/ty.hh>

namespace ucc
{
    namespace ast
    {
        class Expr;

        /// Represents an array type in the ast
        class ArrayTy : public Ty
        {
            public:
                /// \brief  Constructor
                /// \param  loc The location of the ArrayTy
                ArrayTy(const ucmp::misc::location& loc);

                /// \brief  Constructor
                /// \param  loc     The location of the ArrayTy
                /// \param  expr    The size of the ArrayTy
                ArrayTy(const ucmp::misc::location& loc, Expr* expr);

                /// Destructor
                virtual ~ArrayTy();

                /// Return the Ty held by the ArrayTy
                const Ty* sub_ty_get() const
                {
                    return sub_ty_;
                }

                /// Return the Ty held by the ArrayTy
                Ty* sub_ty_get()
                {
                    return sub_ty_;
                }

                /// Return the size of the ArrayTy
                const Expr* size_get() const
                {
                    return size_;
                }

                /// Return the size of the ArrayTy
                Expr* size_get()
                {
                    return size_;
                }

                virtual bool extends_ty(Ty *t) override;

                virtual void accept(Visitor& v) override
                {
                    v(*this);
                }

                virtual void accept(ConstVisitor& v) const override
                {
                    v(*this);
                }

            private:
                Ty* sub_ty_;
                Expr* size_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ARRAY_TY_HH */
