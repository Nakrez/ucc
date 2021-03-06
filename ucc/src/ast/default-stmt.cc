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

#include <ast/default-stmt.hh>

using namespace ucc;
using namespace ast;

DefaultStmt::DefaultStmt(const ucc::misc::location& loc, Stmt* body)
    : Stmt(loc)
    , body_(body)
{}

DefaultStmt::~DefaultStmt()
{
    delete body_;
}

const Stmt* DefaultStmt::body_get() const
{
    return body_;
}

Stmt* DefaultStmt::body_get()
{
    return body_;
}

void DefaultStmt::accept(Visitor& v)
{
    v(*this);
}

void DefaultStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
