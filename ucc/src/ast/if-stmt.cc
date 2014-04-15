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

#include <ast/if-stmt.hh>
#include <ast/expr.hh>

using namespace ucc;
using namespace ast;

IfStmt::IfStmt(const ucc::misc::location& loc,
               Expr* cond,
               Stmt* if_body,
               Stmt* else_body)
    : Stmt(loc)
    , cond_(cond)
    , if_(if_body)
    , else_(else_body)
{}

IfStmt::~IfStmt()
{
    delete cond_;
    delete if_;
    delete else_;
}

const Expr* IfStmt::cond_get() const
{
    return cond_;
}

Expr* IfStmt::cond_get()
{
    return cond_;
}

const Stmt* IfStmt::if_body_get() const
{
    return if_;
}

Stmt* IfStmt::if_body_get()
{
    return if_;
}

const Stmt* IfStmt::else_body_get() const
{
    return else_;
}

Stmt* IfStmt::else_body_get()
{
    return else_;
}

void IfStmt::accept(Visitor& v)
{
    v(*this);
}

void IfStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
