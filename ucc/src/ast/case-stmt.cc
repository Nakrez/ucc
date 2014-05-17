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

#include <ast/case-stmt.hh>

using namespace ucc;
using namespace ast;

CaseStmt::CaseStmt(const ucmp::misc::location& loc,
                   Expr* expr,
                   Stmt* body)
    : Stmt(loc)
    , expr_(expr)
    , body_(body)
{}

CaseStmt::~CaseStmt()
{
    delete expr_;
    delete body_;
}

const Expr* CaseStmt::expr_get() const
{
    return expr_;
}

Expr* CaseStmt::expr_get()
{
    return expr_;
}

const Stmt* CaseStmt::body_get() const
{
    return body_;
}

Stmt* CaseStmt::body_get()
{
    return body_;
}

void CaseStmt::accept(Visitor& v)
{
    v(*this);
}

void CaseStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
