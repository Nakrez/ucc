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

#include <ast/label-stmt.hh>

using namespace ucc;
using namespace ast;

LabelStmt::LabelStmt(const ucc::misc::location& loc,
                     const ucc::misc::Symbol& sym,
                     Stmt* stmt)
    : Stmt(loc)
    , name_(sym)
    , stmt_(stmt)
{}

LabelStmt::~LabelStmt()
{
    delete stmt_;
}

const ucc::misc::Symbol& LabelStmt::name_get() const
{
    return name_;
}

ucc::misc::Symbol& LabelStmt::name_get()
{
    return name_;
}

const Stmt* LabelStmt::stmt_get() const
{
    return stmt_;
}

Stmt* LabelStmt::stmt_get()
{
    return stmt_;
}

void LabelStmt::accept(Visitor& v)
{
    v(*this);
}

void LabelStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
