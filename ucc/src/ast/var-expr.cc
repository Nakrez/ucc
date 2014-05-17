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

#include <ast/var-expr.hh>

using namespace ucc;
using namespace ast;

VarExpr::VarExpr(const ucmp::misc::location& loc,
                 const ucmp::misc::Symbol& sym)
    : Expr(loc)
    , name_(sym)
    , def_(nullptr)
{}

VarExpr::~VarExpr()
{}

const ucmp::misc::Symbol& VarExpr::name_get() const
{
    return name_;
}

ucmp::misc::Symbol& VarExpr::name_get()
{
    return name_;
}

const Decl* VarExpr::def_get() const
{
    return def_;
}

Decl* VarExpr::def_get()
{
    return def_;
}

void VarExpr::def_set(Decl* def)
{
    def_ = def;
}

void VarExpr::accept(Visitor& v)
{
    v(*this);
}

void VarExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
