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

#ifndef UCC_AST_TY_HH
# define UCC_AST_TY_HH

# include <ast/ast.hh>

namespace ucc
{
    namespace ast
    {
        /// Abstract class that represents a type node in the ast
        class Ty: public Ast
        {
            public:
                /// \brief  Constructor
                /// \param  loc     The location of the Type node
                Ty(const ucc::misc::location& loc)
                    : Ast(loc)
                    , is_const_(false)
                    , is_volatile_(false)
                    , is_restrict_(false)
                    , is_unsigned_(false)
                {}

                /// Destructor
                virtual ~Ty() = default;

                /// Return true if the Ty is const
                bool is_const() const
                {
                    return is_const_;
                }

                /// Return true if the Ty is volatile
                bool is_volatile() const
                {
                    return is_volatile_;
                }

                /// Return true if the Ty is restrict
                bool is_restrict() const
                {
                    return is_restrict_;
                }

                /// Return true if the Ty is unsigned
                bool is_unsigned() const
                {
                    return is_unsigned_;
                }

                /// \brief  Set the constness of the Ty
                /// \param  b   if true the Ty is set as const
                void const_set(bool b = true)
                {
                    is_const_ = b;
                }

                /// \brief  Set the Ty as volatile
                /// \param  b   if true the Ty is set as volatile
                void volatile_set(bool b = true)
                {
                    is_volatile_ = b;
                }

                /// \brief  Set the Ty as restrict
                /// \param  b   if true the Ty is set as restrict
                void restrict_set(bool b = true)
                {
                    is_restrict_ = b;
                }

                /// \brief  Set the Ty as unsigned
                /// \param  b   if true the Ty is set as unsigned
                void unsigned_set(bool b = true)
                {
                    is_unsigned_ = b;
                }

                /// \brief  Extends the current Ty
                /// \param  t   The Ty you want to extend the current Ty with
                /// \return true is success, false otherwise
                virtual bool extends_ty(Ty *t) = 0;

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;

            private:
                bool is_const_;
                bool is_volatile_;
                bool is_restrict_;
                bool is_unsigned_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_TY_HH */
