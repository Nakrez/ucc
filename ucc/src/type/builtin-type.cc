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

#include <type/builtin-type.hh>

using namespace ucc;
using namespace type;

/*
    Float Type
*/

Type::TypeCompatibility
Float::compatible_on_assign(const Type& t,
                            ast::AssignExpr::AssignOp) const
{
    const Type* type = &t.actual_type();

    if (dynamic_cast<const Number*> (type))
        return Type::TypeCompatibility::full;

    return Type::TypeCompatibility::error;
}

Type::TypeCompatibility Float::compatible_on_op(const Type& t,
                                                ast::OpExpr::Op) const
{
    const Type* type = &t.actual_type();

    if (dynamic_cast<const Number*> (type))
        return Type::TypeCompatibility::full;

    return Type::TypeCompatibility::error;
}

/*
    Double Type
*/

Type::TypeCompatibility
Double::compatible_on_assign(const Type& t,
                             ast::AssignExpr::AssignOp) const
{
    const Type* type = &t.actual_type();

    if (dynamic_cast<const Number*> (type))
        return Type::TypeCompatibility::full;

    return Type::TypeCompatibility::error;
}

Type::TypeCompatibility Double::compatible_on_op(const Type& t,
                                                 ast::OpExpr::Op) const
{
    const Type* type = &t.actual_type();

    if (dynamic_cast<const Number*> (type))
        return Type::TypeCompatibility::full;

    return Type::TypeCompatibility::error;
}

/*
    Char Type
*/

Type::TypeCompatibility
Char::compatible_on_assign(const Type& t,
                           ast::AssignExpr::AssignOp) const
{
    const Type* type = &t.actual_type();

    if (dynamic_cast<const Number*> (type))
        return Type::TypeCompatibility::warning;

    return Type::TypeCompatibility::error;
}

Type::TypeCompatibility Char::compatible_on_op(const Type& t,
                                               ast::OpExpr::Op) const
{
    const Type* type = &t.actual_type();

    if (dynamic_cast<const Number*> (type))
    {
        if (dynamic_cast<const SignedNumber*> (type) ||
            dynamic_cast<const FloatingPoint*> (type))
        return Type::TypeCompatibility::full;

        return Type::TypeCompatibility::warning;
    }

    return Type::TypeCompatibility::error;
}
