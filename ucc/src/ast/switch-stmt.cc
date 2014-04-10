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

#include <ast/switch-stmt.hh>
#include <ast/expr.hh>

using namespace ucc;
using namespace ast;

SwitchStmt::SwitchStmt(const ucc::parse::location& loc,
                       Expr* cond,
                       Stmt* body)
    : Stmt(loc)
    , cond_(cond)
    , body_(body)
{}

SwitchStmt::~SwitchStmt()
{
    delete cond_;
    delete body_;
}

const Expr* SwitchStmt::cond_get() const
{
    return cond_;
}

Expr* SwitchStmt::cond_get()
{
    return cond_;
}

const Stmt* SwitchStmt::body_get() const
{
    return body_;
}

Stmt* SwitchStmt::body_get()
{
    return body_;
}

void SwitchStmt::accept(Visitor& v)
{
    v(*this);
}

void SwitchStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
