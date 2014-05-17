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

CompoundStmt::CompoundStmt(const ucmp::misc::location& loc,
                           AstList* compound)
    : Stmt(loc)
    , compound_(compound)
{}

CompoundStmt::~CompoundStmt()
{
    delete compound_;
}

const AstList* CompoundStmt::compound_get() const
{
    return compound_;
}

AstList* CompoundStmt::compound_get()
{
    return compound_;
}

void CompoundStmt::accept(Visitor& v)
{
    v(*this);
}

void CompoundStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
