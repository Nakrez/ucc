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

#ifndef UCC_AST_TYPE_USER_HH
# define UCC_AST_TYPE_USER_HH

# include <type/type.hh>

namespace ucc
{
    namespace ast
    {
        /// Used by ast nodes that use types
        class TypeUser
        {
            public:
                /// Constructor
                TypeUser();

                /// Destructor
                virtual ~TypeUser();

                /// Return the used type
                const type::Type* type_get() const
                {
                    return type_;
                }

                /// \brief  Set the used type
                /// \param  t   The type you want to set as used by the ast
                ///             node
                void type_set(const type::Type* t)
                {
                    type_ = t;
                }

            protected:
                const type::Type* type_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_TYPE_USER_HH */
