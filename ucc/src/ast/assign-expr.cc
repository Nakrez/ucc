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

#include <cassert>

#include <ast/assign-expr.hh>

using namespace ucc;
using namespace ast;

AssignExpr::AssignExpr(const ucc::misc::location& loc,
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

OpExpr::Op ast::assign_op_to_op_expr(AssignExpr::AssignOp op)
{
    switch (op)
    {
        case AssignExpr::AssignOp::MUL_ASSIGN:
            return OpExpr::Op::OP_MUL;
        case AssignExpr::AssignOp::DIV_ASSIGN:
            return OpExpr::Op::OP_DIV;
        case AssignExpr::AssignOp::MOD_ASSIGN:
            return OpExpr::Op::OP_MOD;
        case AssignExpr::AssignOp::PLUS_ASSIGN:
            return OpExpr::Op::OP_PLUS;
        case AssignExpr::AssignOp::MINUS_ASSIGN:
            return OpExpr::Op::OP_MINUS;
        case AssignExpr::AssignOp::LSHIFT_ASSIGN:
            return OpExpr::Op::OP_LSHIFT;
        case AssignExpr::AssignOp::RSHIFT_ASSIGN:
            return OpExpr::Op::OP_RSHIFT;
        case AssignExpr::AssignOp::BAND_ASSIGN:
            return OpExpr::Op::OP_BAND;
        case AssignExpr::AssignOp::BXOR_ASSIGN:
            return OpExpr::Op::OP_XOR;
        case AssignExpr::AssignOp::BOR_ASSIGN:
            return OpExpr::Op::OP_BOR;
        default:
            assert(false &&
                   "Internal error: cannot convert assign op to op expr");
    }
}
