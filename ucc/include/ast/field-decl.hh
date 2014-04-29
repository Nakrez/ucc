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

#ifndef UCC_AST_FIELD_DECL_HH
# define UCC_AST_FIELD_DECL_HH

# include <ast/decl.hh>
# include <ast/ty.hh>
# include <ast/expr.hh>
# include <ast/type-builder.hh>

namespace ucc
{
    namespace ast
    {
        class FieldDecl : public Decl, public TypeBuilder
        {
            public:
                /// \brief  Constructor
                /// \param  loc         The location of the field
                /// \param  name        The name of the field
                /// \param  ty          The type of the field
                /// \param  bit_field   The bit field expression
                FieldDecl(const ucc::misc::location& loc,
                          const ucc::misc::Symbol& name,
                          Ty* ty,
                          Expr* bit_field);

                /// Destructor
                virtual ~FieldDecl();

                /// Return the type of the field
                const Ty* ty_get() const
                {
                    return ty_;
                }

                /// Return the type of the field
                Ty* ty_get()
                {
                    return ty_;
                }

                /// Return the bit field value
                const Expr* bit_field_get() const
                {
                    return bit_field_;
                }

                /// Return the bit field value
                Expr* bit_field_get()
                {
                    return bit_field_;
                }

                /// Set the type of the field
                void ty_set(Ty* t)
                {
                    ty_ = t;
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
                Expr* bit_field_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FIELD_DECL_HH */
