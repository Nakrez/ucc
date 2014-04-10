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

#include <ast/assign-expr.hh>

using namespace ucc;
using namespace ast;

AssignExpr::AssignExpr(const ucc::parse::location& loc,
                       Expr* lvalue,
                       AssignOp op,
                       Expr* rvalue)
    : Expr(loc)
    , lvalue_(lvalue)
    , rvalue_(rvalue)
    , op_(op)
{}

AssignExpr::~AssignExpr()
{
    delete lvalue_;
    delete rvalue_;
}

const Expr* AssignExpr::lvalue_get() const
{
    return lvalue_;
}

Expr* AssignExpr::lvalue_get()
{
    return lvalue_;
}

const Expr* AssignExpr::rvalue_get() const
{
    return rvalue_;
}

Expr* AssignExpr::rvalue_get()
{
    return rvalue_;
}

AssignExpr::AssignOp AssignExpr::op_get() const
{
    return op_;
}

std::string AssignExpr::op_to_str() const
{
    switch (op_)
    {
        case ASSIGN:
            return "=";
        case MUL_ASSIGN:
            return "*=";
        case DIV_ASSIGN:
            return "/=";
        case MOD_ASSIGN:
            return "%=";
        case PLUS_ASSIGN:
            return "+=";
        case MINUS_ASSIGN:
            return "-=";
        case LSHIFT_ASSIGN:
            return "<<=";
        case RSHIFT_ASSIGN:
            return ">>=";
        case BAND_ASSIGN:
            return "&=";
        case BXOR_ASSIGN:
            return "^=";
        case BOR_ASSIGN:
            return "|=";
    }
}

void AssignExpr::accept(Visitor& v)
{
    v(*this);
}

void AssignExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
