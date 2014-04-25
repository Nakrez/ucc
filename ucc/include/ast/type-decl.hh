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

#ifndef UCC_AST_TYPE_DECL_HH
# define UCC_AST_TYPE_DECL_HH

# include <ast/decl.hh>

# include <ast/type-builder.hh>

namespace ucc
{
    namespace ast
    {
        class Ty;

        /// Represent a type declaration in the ast
        class TypeDecl : public Decl, public TypeBuilder
        {
            public:
                /// \brief  Constructor
                /// \param  loc     The location of the TypeDecl
                /// \param  name    The name defined by the TypeDecl
                /// \param  ty      The type defined by the TypeDecl
                TypeDecl(const ucc::misc::location& loc,
                         const ucc::misc::Symbol& name,
                         Ty* ty);

                /// Destructor
                virtual ~TypeDecl();

                /// Return the type declared by the TypeDecl
                const Ty* ty_get() const
                {
                    return ty_;
                }

                /// Return the type declared by the TypeDecl
                Ty* ty_get()
                {
                    return ty_;
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
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_TYPE_DECL_HH */
