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

#ifndef UCC_AST_ENUM_TY_HH
# define UCC_AST_ENUM_TY_HH

# include <misc/symbol.hh>

# include <ast/enum-decl.hh>
# include <ast/ty.hh>

namespace ucc
{
    namespace ast
    {
        /// Represents an enumeration type on the ast
        class EnumTy : public Ty
        {
            public:
                /// \brief  Constructor
                /// \param  loc     The location of the EnumTy
                /// \param  name    The name of the EnumTy
                EnumTy(const ucmp::misc::location& loc,
                       const ucmp::misc::Symbol& name);

                /// Destructor
                virtual ~EnumTy() = default;

                /// Return the name of the EnumTy
                const ucmp::misc::Symbol& name_get() const
                {
                    return name_;
                }

                /// Return the name of the EnumTy
                ucmp::misc::Symbol& name_get()
                {
                    return name_;
                }

                /// Return the definition node
                const EnumDecl* def_get() const
                {
                    return def_;
                }

                /// Return the definition node
                EnumDecl* def_get()
                {
                    return def_;
                }

                /// \brief  Set the definition node
                /// \param  def The new definition node
                void def_set(EnumDecl* def)
                {
                    def_ = def;
                }

                virtual bool extends_ty(Ty*) override
                {
                    return false;
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
                ucmp::misc::Symbol name_;
                EnumDecl* def_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ENUM_TYPE_HH */
