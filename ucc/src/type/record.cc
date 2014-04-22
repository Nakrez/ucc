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

#include <type/record.hh>

using namespace ucc;
using namespace type;

const Type* Record::field_type_get(const ucc::misc::Symbol name) const
{
    for (auto field : fields_)
    {
        if (field.name_get() == name)
            return field.type_get();
    }

    return nullptr;
}

Type::TypeCompatibility
Record::compatible_on_assign(const Type& t,
                             ast::AssignExpr::AssignOp op) const
{
    if (op != ast::AssignExpr::AssignOp::ASSIGN)
        return Type::TypeCompatibility::error;

    if (&t != this)
        return Type::TypeCompatibility::error;

    return Type::TypeCompatibility::full;
}
