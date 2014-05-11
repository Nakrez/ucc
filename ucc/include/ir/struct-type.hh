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

#ifndef UCC_IR_STRUCT_TYPE_HH
# define UCC_IR_STRUCT_TYPE_HH

# include <list>

# include <misc/symbol.hh>
# include <ir/type.hh>

namespace ucc
{
    namespace ir
    {
        class Context;

        class StructType : public Type
        {
            public:
                StructType(Context& c,
                           const misc::Symbol& name,
                           const std::list<sType>& types);
                virtual ~StructType() = default;

            protected:
                misc::Symbol name_;
                std::list<sType> types_;
        };

        typedef std::shared_ptr<StructType> sStructType;
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_STRUCT_TYPE_HH */
