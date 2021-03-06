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

#include <type/array.hh>
#include <type/integer.hh>
#include <type/ptr.hh>

using namespace ucc;
using namespace type;

Array::Array(const Type* inner_type)
    : inner_type_(inner_type)
{}

Type::TypeCompatibility
Array::compatible_on_assign(const Type& t) const
{
    const Array* a = dynamic_cast<const Array*> (&t.actual_type());
    const Ptr* p = dynamic_cast<const Ptr*> (&t.actual_type());

    if (a)
        return Type::TypeCompatibility::warning;
    else if (p)
        return Type::TypeCompatibility::warning;

    return Type::TypeCompatibility::error;
}

Type::TypeCompatibility
Array::compatible_on_op(const Type& t,
                        ast::OpExpr::Op op) const
{
    if ((op == ast::OpExpr::Op::OP_PLUS || op == ast::OpExpr::Op::OP_PLUS) &&
        dynamic_cast<const Integer*>(&t.actual_type()))
        return Type::TypeCompatibility::full;

    return Type::TypeCompatibility::error;
}
