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

#include <ast/ptr-type.hh>

using namespace ucc;
using namespace ast;

PtrType::PtrType(const ucc::parse::location& loc)
    : Type(loc)
    , pointed_type_(nullptr)
{}

PtrType::PtrType(const ucc::parse::location& loc, Type* pointed_type)
    : Type(loc)
    , pointed_type_(pointed_type)
{}

PtrType::~PtrType()
{
    delete pointed_type_;
}

const Type* PtrType::pointed_type_get() const
{
    return pointed_type_;
}

Type* PtrType::pointed_type_get()
{
    return pointed_type_;
}

bool PtrType::extends_type(Type *t)
{
    if (!pointed_type_)
    {
        pointed_type_ = t;
        return true;
    }

    return pointed_type_->extends_type(t);
}

void PtrType::accept(Visitor& v)
{
    v(*this);
}

void PtrType::accept(ConstVisitor& v) const
{
    v(*this);
}
