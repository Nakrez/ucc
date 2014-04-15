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

#include <ast/field-decl.hh>

using namespace ucc;
using namespace ast;

FieldDecl::FieldDecl(const ucc::misc::location& loc,
                     const ucc::misc::Symbol& name,
                     Type* type,
                     Expr* bit_field)
    : Decl(loc, name)
    , type_(type)
    , bit_field_(bit_field)
{}

FieldDecl::~FieldDecl()
{
    delete type_;
    delete bit_field_;
}

const Type* FieldDecl::type_get() const
{
    return type_;
}

Type* FieldDecl::type_get()
{
    return type_;
}

const Expr* FieldDecl::bit_field_get() const
{
    return bit_field_;
}

Expr* FieldDecl::bit_field_get()
{
    return bit_field_;
}

void FieldDecl::type_set(Type* t)
{
    type_ = t;
}

void FieldDecl::accept(Visitor& v)
{
    v(*this);
}

void FieldDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
