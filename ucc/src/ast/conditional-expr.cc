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

#include <ast/conditional-expr.hh>

using namespace ucc;
using namespace ast;

ConditionalExpr::ConditionalExpr(const ucc::misc::location& loc,
                                 Expr* cond,
                                 Expr* true_expr,
                                 Expr* false_expr)
    : Expr(loc)
    , cond_(cond)
    , true_(true_expr)
    , false_(false_expr)
{}

ConditionalExpr::~ConditionalExpr()
{
    delete cond_;
    delete true_;
    delete false_;
}

const Expr* ConditionalExpr::cond_get() const
{
    return cond_;
}

Expr* ConditionalExpr::cond_get()
{
    return cond_;
}

const Expr* ConditionalExpr::true_expr_get() const
{
    return true_;
}

Expr* ConditionalExpr::true_expr_get()
{
    return true_;
}

const Expr* ConditionalExpr::false_expr_get() const
{
    return false_;
}

Expr* ConditionalExpr::false_expr_get()
{
    return false_;
}

void ConditionalExpr::accept(Visitor& v)
{
    v(*this);
}

void ConditionalExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
