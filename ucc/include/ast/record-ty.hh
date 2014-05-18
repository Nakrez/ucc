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

#ifndef UCC_AST_RECORD_TY_HH
# define UCC_AST_RECORD_TY_HH

# include <ucmp/misc/symbol.hh>

# include <ast/ty.hh>
# include <ast/record-decl.hh>

namespace ucc
{
    namespace ast
    {
        /// Represents a record type in the ast
        class RecordTy : public Ty
        {
            public:
                /// \brief  Constructor
                /// \param  loc         The location of the RecordTy
                /// \param  record_type The type of the RecordTy
                ///                     (struct or union)
                /// \param  name        The name of the RecordTy
                RecordTy(const ucmp::misc::location& loc,
                         RecordDecl::RecordType record_type,
                         const ucmp::misc::Symbol& name);

                /// Destructor
                virtual ~RecordTy() = default;

                /// Return the name of the RecordTy
                const ucmp::misc::Symbol& name_get() const
                {
                    return name_;
                }

                /// Return the name of the RecordTy
                ucmp::misc::Symbol& name_get()
                {
                    return name_;
                }

                /// Return the record type (struct or union)
                RecordDecl::RecordType record_type_get() const
                {
                    return record_type_;
                }

                /// Return the definition node
                const RecordDecl* def_get() const
                {
                    return def_;
                }

                /// Return the definition node
                RecordDecl* def_get()
                {
                    return def_;
                }

                /// \brief  Set the definition node
                /// \param  def The record definition
                void def_set(RecordDecl* def)
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

            private:
                ucmp::misc::Symbol name_;
                RecordDecl::RecordType record_type_;
                RecordDecl* def_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_RECORD_TY_HH */
