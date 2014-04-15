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

#include <ast/enum-type.hh>

using namespace ucc;
using namespace ast;

EnumType::EnumType(const ucc::misc::location& loc,
                   const ucc::misc::Symbol& name)
    : Type(loc)
    , name_(name)
    , def_(nullptr)
{}

EnumType::~EnumType()
{}

const ucc::misc::Symbol& EnumType::name_get() const
{
    return name_;
}

ucc::misc::Symbol& EnumType::name_get()
{
    return name_;
}

const EnumDecl* EnumType::def_get() const
{
    return def_;
}

EnumDecl* EnumType::def_get()
{
    return def_;
}

void EnumType::def_set(EnumDecl* def)
{
    def_ = def;
}

void EnumType::accept(Visitor& v)
{
    v(*this);
}

void EnumType::accept(ConstVisitor& v) const
{
    v(*this);
}
