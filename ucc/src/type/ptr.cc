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

#include <type/ptr.hh>
#include <type/builtin-type.hh>

using namespace ucc;
using namespace type;

Ptr::Ptr(const Type* pointed_type)
    : pointed_type_(pointed_type)
{}

Ptr::~Ptr()
{}

Type::TypeCompatibility
Ptr::compatible_on_assign(const Type& t,
        ast::AssignExpr::AssignOp op) const
{
    if (op == ast::AssignExpr::AssignOp::ASSIGN)
    {
        const Type* type = &t.actual_type();
        const Ptr* ptr = dynamic_cast<const Ptr*> (type);

        if (ptr)
        {
            if (ptr->is_void_ptr() || is_void_ptr())
                return Type::TypeCompatibility::full;

            /* TODO: Check compatibility between pointers */
            return Type::TypeCompatibility::full;
        }

        if (dynamic_cast<const Integer*> (type))
        {
            return Type::TypeCompatibility::warning;
        }

        return Type::TypeCompatibility::error;
    }

    return compatible_on_op(t, ast::assign_op_to_op_expr(op));
}

Type::TypeCompatibility
Ptr::compatible_on_op(const Type& t,
                      ast::OpExpr::Op op) const
{
    const Type* type = &t.actual_type();

    if (!dynamic_cast<const Integer*> (type))
        return Type::TypeCompatibility::error;

    if (op == ast::OpExpr::Op::OP_PLUS || op == ast::OpExpr::Op::OP_MINUS)
        return Type::TypeCompatibility::full;

    return Type::TypeCompatibility::error;
}
