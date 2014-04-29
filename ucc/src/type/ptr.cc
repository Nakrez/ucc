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
#include <type/const.hh>
#include <type/named.hh>
#include <type/array.hh>
#include <type/function.hh>

using namespace ucc;
using namespace type;

Ptr::Ptr(const Type* pointed_type)
    : pointed_type_(pointed_type)
{}

Ptr::~Ptr()
{}

bool Ptr::operator==(const Type& t) const
{
    const Ptr* p = dynamic_cast<const Ptr*> (&t);
    const Named* n = dynamic_cast<const Named*> (&t);
    const Array* a = dynamic_cast<const Array*> (&t);

    if (p)
        return *pointed_type_ == *p->pointed_type_get();
    else if (n)
        return *this == *n->alias_get();
    else if (a)
        return *pointed_type_ == *a->inner_type_get();

    return false;
}

Type::TypeCompatibility
Ptr::compatible_on_assign(const Type& t) const
{
    const Type* type = &t.actual_type();
    const Ptr* ptr = dynamic_cast<const Ptr*> (type);
    const Array* a = dynamic_cast<const Array*> (type);
    const Function* f = dynamic_cast<const Function*> (type);

    if (ptr)
    {
        if (ptr->is_void_ptr() || is_void_ptr())
            return Type::TypeCompatibility::full;

        return (*pointed_type_ == *ptr->pointed_type_get()) ?
               Type::TypeCompatibility::full :
               Type::TypeCompatibility::warning;
    }

    if (a)
        return (*this == *a) ? Type::TypeCompatibility::full :
               Type::TypeCompatibility::warning;

    if (f)
        return (*pointed_type_ == *f) ? Type::TypeCompatibility::full :
               Type::TypeCompatibility::warning;

    if (dynamic_cast<const Integer*> (type))
        return Type::TypeCompatibility::warning;

    return Type::TypeCompatibility::error;
}

Type::TypeCompatibility
Ptr::compatible_on_op(const Type& t,
                      ast::OpExpr::Op op) const
{
    const Type* type = &t.actual_type();
    const Ptr* ptr = dynamic_cast<const Ptr*> (&t.actual_type());

    if (ptr &&
        op >= ast::OpExpr::Op::OP_GT &&
        op <= ast::OpExpr::Op::OP_DIFF)
    {
        if (is_void_ptr() || ptr->is_void_ptr())
            return Type::TypeCompatibility::full;

        if (*pointed_type_ == *ptr->pointed_type_get())
            return Type::TypeCompatibility::full;

        return Type::TypeCompatibility::warning;
    }

    if (!dynamic_cast<const Integer*> (type))
        return Type::TypeCompatibility::error;

    if (op == ast::OpExpr::Op::OP_PLUS || op == ast::OpExpr::Op::OP_MINUS)
        return Type::TypeCompatibility::full;

    return Type::TypeCompatibility::error;
}
