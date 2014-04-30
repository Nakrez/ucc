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

#ifndef UCC_AST_VAR_DECL_HH
# define UCC_AST_VAR_DECL_HH

# include <ast/decl.hh>
# include <ast/expr.hh>
# include <ast/ty.hh>
# include <ast/type-user.hh>

namespace ucc
{
    namespace ast
    {
        /// Represent a variable declaration in the ast
        class VarDecl : public Decl, public TypeUser
        {
            public:
                /// \brief  Constructor
                /// \param  loc     The location of the VarDecl
                /// \param  name    The name of the variable declared
                /// \param  ty      The type of the variable declared
                /// \param  e       The init expression
                VarDecl(const ucc::misc::location& loc,
                        const ucc::misc::Symbol& name,
                        Ty* ty,
                        Expr* e);

                /// \brief  Constructor
                /// \param  loc     The location of the VarDecl
                VarDecl(const ucc::misc::location& loc);

                /// Destructor
                virtual ~VarDecl();

                /// Return the type of the variable
                const Ty* ty_get() const
                {
                    return ty_;
                }

                /// Return the type of the variable
                Ty* ty_get()
                {
                    return ty_;
                }

                /// Return the init value of the variable
                const Expr* init_get() const
                {
                    return init_;
                }

                /// Return the init value of the variable
                Expr* init_get()
                {
                    return init_;
                }

                /// Get the previous declaration of the variable
                const VarDecl* prev_get() const
                {
                    return prev_;
                }

                /// Get the previous declaration of the variable
                VarDecl* prev_get()
                {
                    return prev_;
                }

                /// \brief  Set the previous declaration of the variable
                /// \param  d   The previous declaration of the variable
                void prev_set(VarDecl* d)
                {
                    prev_ = d;
                }

                /// Return true if the variable is an elispis
                bool is_elipsis() const
                {
                    return is_elipsis_;
                }

                bool is_initialized() const
                {
                    return initialized_;
                }

                void set_initialized(bool b = true)
                {
                    initialized_ = b;
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
                Ty* ty_;
                Expr* init_;
                bool is_elipsis_;
                bool initialized_;
                VarDecl* prev_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_VAR_DECL_HH */
