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

#ifndef UCC_TYPE_FIELD_HH
# define UCC_TYPE_FIELD_HH

# include <misc/symbol.hh>

# include <type/type.hh>

namespace ucc
{
    namespace type
    {
        class Field
        {
            public:
                /// \brief  Constructor
                /// \param  name    The name of the field
                /// \param  type    The type of the field
                Field(const ucc::misc::Symbol name, const Type* type)
                    : name_(name)
                    , type_(type)
                {}

                /// Destructor
                ~Field() = default;

                /// Return the name of the field
                const ucc::misc::Symbol& name_get() const
                {
                    return name_;
                }

                /// Return the type of the field
                const Type* type_get() const
                {
                    return type_;
                }

            private:
                ucc::misc::Symbol name_;
                const Type* type_;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_FIELD_HH */
