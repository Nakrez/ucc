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

#include <ast/array-type.hh>
#include <ast/expr.hh>

using namespace ucc;
using namespace ast;

ArrayType::ArrayType(const ucc::misc::location& loc)
    : Type(loc)
    , sub_type_(nullptr)
    , size_(nullptr)
{}

ArrayType::ArrayType(const ucc::misc::location& loc, Expr* expr)
    : Type(loc)
    , sub_type_(nullptr)
    , size_(expr)
{}

ArrayType::~ArrayType()
{
    delete sub_type_;
    delete size_;
}

const Type* ArrayType::sub_type_get() const
{
    return sub_type_;
}

Type* ArrayType::sub_type_get()
{
    return sub_type_;
}

const Expr* ArrayType::size_get() const
{
    return size_;
}

Expr* ArrayType::size_get()
{
    return size_;
}

bool ArrayType::extends_type(Type *t)
{
    if (sub_type_ == nullptr)
    {
        sub_type_ = t;

        return t;
    }

    return sub_type_->extends_type(t);
}

void ArrayType::accept(Visitor& v)
{
    v(*this);
}

void ArrayType::accept(ConstVisitor& v) const
{
    v(*this);
}
