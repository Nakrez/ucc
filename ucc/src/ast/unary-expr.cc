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

#include <ast/unary-expr.hh>

using namespace ucc;
using namespace ast;

UnaryExpr::UnaryExpr(const ucmp::misc::location& loc,
                     UnaryOp op,
                     Expr* expr)
    : Expr(loc)
    , expr_(expr)
    , op_(op)
{}

UnaryExpr::~UnaryExpr()
{
    delete expr_;
}

UnaryExpr::UnaryOp UnaryExpr::op_get() const
{
    return op_;
}

std::string UnaryExpr::op_to_str() const
{
    switch (op_)
    {
        case BAND:
            return "&";
        case DEREF:
            return "*";
        case PLUS:
            return "+";
        case MINUS:
            return "-";
        case TILDE:
            return "~";
        case BANG:
            return "!";
        case PRE_INCR:
            return "++";
        case PRE_DECR:
            return "--";
        case POST_INCR:
            return "++";
        case POST_DECR:
            return "--";
    }
}


const Expr* UnaryExpr::expr_get() const
{
    return expr_;
}

Expr* UnaryExpr::expr_get()
{
    return expr_;
}

void UnaryExpr::accept(Visitor& v)
{
    v(*this);
}

void UnaryExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
