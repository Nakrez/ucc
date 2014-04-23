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

#ifndef UCC_AST_TYPE_BUILDER_HH
# define UCC_AST_TYPE_BUILDER_HH

# include <type/type.hh>

namespace ucc
{
    namespace ast
    {
        /// Represent ast node that create a new type
        class TypeBuilder
        {
            public:
                /// Constructor
                TypeBuilder();

                /// Destructor
                virtual ~TypeBuilder();

                /// \brief  Set the built type
                /// \param  t   The built type you want to set
                void built_type_set(const type::Type* t)
                {
                    built_type_ = t;
                }

                /// Return the built type
                const type::Type* built_type_get() const
                {
                    return built_type_;
                }

            protected:
                const type::Type* built_type_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_TYPE_BUILDER_HH */
