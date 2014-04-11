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

#include <ast/all.hh>

using namespace ucc;
using namespace ast;

CallExpr::CallExpr(const ucc::parse::location& loc,
                   Expr* var,
                   ExprList* param)
    : Expr(loc)
    , var_(var)
    , param_(param)
    , def_(nullptr)
{}

CallExpr::~CallExpr()
{
    delete var_;
    delete param_;
}

const Expr* CallExpr::var_get() const
{
    return var_;
}

Expr* CallExpr::var_get()
{
    return var_;
}

const ExprList* CallExpr::param_get() const
{
    return param_;
}

ExprList* CallExpr::param_get()
{
    return param_;
}

const FunctionDecl* CallExpr::def_get() const
{
    return def_;
}

FunctionDecl* CallExpr::def_get()
{
    return def_;
}

void CallExpr::def_set(FunctionDecl* d)
{
    def_ = d;
}

void CallExpr::accept(Visitor& v)
{
    v(*this);
}

void CallExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
