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

#ifndef UCC_AST_NAMED_TY_HH
# define UCC_AST_NAMED_TY_HH

# include <misc/symbol.hh>

# include <ast/ty.hh>
# include <ast/type-decl.hh>

namespace ucc
{
    namespace ast
    {
        /// Represents an alias over a type in the ast
        class NamedTy : public Ty
        {
            public:
                /// \brief  Constructor
                /// \param  loc     The location of the NamedTy
                /// \param  name    The name of the NamedTy
                NamedTy(const ucc::misc::location& loc,
                        const ucc::misc::Symbol& name)
                    : Ty(loc)
                    , name_(name)
                    , def_(nullptr)
                {}

                /// Destructor
                virtual ~NamedTy() = default;

                /// Return the name of the NamedTy
                const ucc::misc::Symbol& name_get() const
                {
                    return name_;
                }

                /// Return the name of the NamedTy
                ucc::misc::Symbol& name_get()
                {
                    return name_;
                }

                /// Return the TypeDecl that defines this NamedTy
                const TypeDecl* def_get() const
                {
                    return def_;
                }

                /// Return the TypeDecl that defines this NamedTy
                TypeDecl* def_get()
                {
                    return def_;
                }

                /// Set the TypeDecl that defines this NamedTy
                void def_set(TypeDecl* d)
                {
                    def_ = d;
                }

                virtual bool extends_ty(Ty*) override
                {
                    return false;
                }

                virtual void accept(Visitor& v) override
                {
                    v(*this);
                }

                virtual void accept(ConstVisitor& v) const
                {
                    v(*this);
                }

            private:
                ucc::misc::Symbol name_;
                TypeDecl* def_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_NAMED_TY_HH */
