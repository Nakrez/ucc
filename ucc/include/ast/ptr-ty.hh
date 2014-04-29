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

#ifndef UCC_AST_PTR_TY_HH
# define UCC_AST_PTR_TY_HH

# include <ast/ty.hh>

namespace ucc
{
    namespace ast
    {
        /// Represents pointer type in the ast
        class PtrTy : public Ty
        {
            public:
                /// \brief  Constructor
                /// \param  loc The location of the PtrTy
                PtrTy(const ucc::misc::location& loc);

                /// \brief  Constructor
                /// \param  loc             The location of the PtrTy
                /// \param  pointed_type    The Ty pointed by the PtrTy
                PtrTy(const ucc::misc::location& loc, Ty* pointed_ty);

                /// Destructor
                virtual ~PtrTy();

                /// Return the Ty pointed by the PtrTy
                const Ty* pointed_ty_get() const
                {
                    return pointed_ty_;
                }

                /// Return the Ty pointed by the PtrTy
                Ty* pointed_ty_get()
                {
                    return pointed_ty_;
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

            protected:
                /// The pointed Ty held by the PtrTy
                Ty* pointed_ty_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_PTR_TY_HH */
