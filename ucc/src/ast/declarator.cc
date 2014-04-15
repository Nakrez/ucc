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

#include <ast/declarator.hh>
#include <ast/all.hh>

using namespace ucc;
using namespace ast;

Declarator::Declarator(const ucc::misc::location& loc,
                       const ucc::misc::Symbol& s)
    : Decl(loc, s)
    , type_(nullptr)
    , init_(nullptr)
{}

Declarator::~Declarator()
{
    /* type_ and init_ are not deleted because it is transfered to a decl */
}

const Type* Declarator::type_get() const
{
    return type_;
}

Type* Declarator::type_get()
{
    return type_;
}

const Expr* Declarator::init_get() const
{
    return init_;
}

Expr* Declarator::init_get()
{
    return init_;
}

void Declarator::init_set(Expr* e)
{
    init_ = e;
}

bool Declarator::extends_type(Type* t)
{
    if (!type_)
    {
        type_ = t;

        return true;
    }

    return type_->extends_type(t);
}

void Declarator::accept(Visitor& v)
{
    v(*this);
}

void Declarator::accept(ConstVisitor& v) const
{
    v(*this);
}
