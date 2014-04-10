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

WhileStmt::WhileStmt(const ucc::parse::location& loc, Expr* cond, Ast* body)
    : Stmt(loc)
    , cond_(cond)
    , body_(body)
{}

WhileStmt::~WhileStmt()
{
    delete cond_;
    delete body_;
}

const Expr* WhileStmt::cond_get() const
{
    return cond_;
}

Expr* WhileStmt::cond_get()
{
    return cond_;
}

const Ast* WhileStmt::body_get() const
{
    return body_;
}

Ast* WhileStmt::body_get()
{
    return body_;
}

void WhileStmt::accept(Visitor& v)
{
    v(*this);
}

void WhileStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
