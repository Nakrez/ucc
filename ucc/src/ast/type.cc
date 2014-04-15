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

#include <ast/type.hh>

using namespace ucc;
using namespace ast;

Type::Type(const ucc::misc::location& loc)
    : Ast(loc)
    , is_const_(false)
    , is_volatile_(false)
    , is_restrict_(false)
    , is_unsigned_(false)
{}

Type::~Type()
{}

bool Type::is_const() const
{
    return is_const_;
}

bool Type::is_volatile() const
{
    return is_volatile_;
}

bool Type::is_restrict() const
{
    return is_restrict_;
}

bool Type::is_unsigned() const
{
    return is_unsigned_;
}

void Type::const_set(bool b)
{
    is_const_ = b;
}

void Type::volatile_set(bool b)
{
    is_volatile_ = b;
}

void Type::restrict_set(bool b)
{
    is_restrict_ = b;
}

void Type::unsigned_set(bool b)
{
    is_unsigned_ = b;
}
