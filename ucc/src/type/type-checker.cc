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

#include <type/type-checker.hh>
# include <type/builtin-type.hh>
# include <type/ptr.hh>
# include <type/named.hh>
# include <type/const.hh>

using namespace ucc;
using namespace type;

TypeChecker::TypeChecker()
{}

TypeChecker::~TypeChecker()
{}

void TypeChecker::operator()(ast::IntExpr& e)
{
    e.type_set(&Int::instance_get());
}

void TypeChecker::operator()(ast::FloatExpr& e)
{
    e.type_set(&Float::instance_get());
}

void TypeChecker::operator()(ast::StringExpr& e)
{
    Const* ctype = new Const(&Char::instance_get());
    Ptr* str_type = new Ptr(ctype);

    e.built_type_set(str_type);
}
