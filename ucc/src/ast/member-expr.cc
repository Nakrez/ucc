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

#include <ast/member-expr.hh>

using namespace ucc;
using namespace ast;

MemberExpr::MemberExpr(const ucmp::misc::location& loc,
                       Expr* lexpr,
                       const ucmp::misc::Symbol& name,
                       bool is_arrow)
    : Expr(loc)
    , lexpr_(lexpr)
    , name_(name)
    , is_arrow_(is_arrow)
{}

MemberExpr::~MemberExpr()
{
    delete lexpr_;
}

const Expr* MemberExpr::lexpr_get() const
{
    return lexpr_;
}

Expr* MemberExpr::lexpr_get()
{
    return lexpr_;
}

const ucmp::misc::Symbol& MemberExpr::name_get() const
{
    return name_;
}

ucmp::misc::Symbol& MemberExpr::name_get()
{
    return name_;
}

bool MemberExpr::is_arrow() const
{
    return is_arrow_;
}

void MemberExpr::accept(Visitor& v)
{
    v(*this);
}

void MemberExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
