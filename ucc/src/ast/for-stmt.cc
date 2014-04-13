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

#include <ast/for-stmt.hh>

using namespace ucc;
using namespace ast;

ForStmt::ForStmt(const ucc::parse::location& loc,
                 Expr* init,
                 Expr* cond,
                 Expr* inc,
                 Stmt* body)
    : Stmt(loc)
    , init_(init)
    , cond_(cond)
    , inc_(inc)
    , body_(body)
{}

ForStmt::~ForStmt()
{
    delete init_;
    delete cond_;
    delete inc_;
    delete body_;
}

const Expr* ForStmt::init_get() const
{
    return init_;
}

Expr* ForStmt::init_get()
{
    return init_;
}

const Expr* ForStmt::cond_get() const
{
    return cond_;
}

Expr* ForStmt::cond_get()
{
    return cond_;
}

const Expr* ForStmt::inc_get() const
{
    return inc_;
}

Expr* ForStmt::inc_get()
{
    return inc_;
}

const Stmt* ForStmt::body_get() const
{
    return body_;
}

Stmt* ForStmt::body_get()
{
    return body_;
}

void ForStmt::accept(Visitor& v)
{
    v(*this);
}

void ForStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
