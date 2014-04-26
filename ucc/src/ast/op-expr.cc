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

#include <ast/op-expr.hh>

using namespace ucc;
using namespace ast;

OpExpr::OpExpr(const ucc::misc::location& loc,
               Expr* lexpr,
               Op op,
               Expr* rexpr)
    : Expr(loc)
    , lexpr_(lexpr)
    , rexpr_(rexpr)
    , op_(op)
{}

OpExpr::~OpExpr()
{
    delete lexpr_;
    delete rexpr_;
}

const Expr* OpExpr::lexpr_get() const
{
    return lexpr_;
}

Expr* OpExpr::lexpr_get()
{
    return lexpr_;
}

const Expr* OpExpr::rexpr_get() const
{
    return rexpr_;
}

Expr* OpExpr::rexpr_get()
{
    return rexpr_;
}

OpExpr::Op OpExpr::op_get() const
{
    return op_;
}

std::string OpExpr::op_to_str() const
{
    switch (op_)
    {
        case OP_PLUS:
            return "+";
        case OP_MINUS:
            return "-";
        case OP_MUL:
            return "*";
        case OP_DIV:
            return "/";
        case OP_MOD:
            return "%";
        case OP_LSHIFT:
            return "<<";
        case OP_RSHIFT:
            return ">>";
        case OP_GT:
            return ">";
        case OP_GE:
            return ">=";
        case OP_LT:
            return "<";
        case OP_LE:
            return "<=";
        case OP_EQ:
            return "==";
        case OP_DIFF:
            return "!=";
        case OP_BAND:
            return "&";
        case OP_XOR:
            return "^";
        case OP_BOR:
            return "|";
        case OP_AND:
            return "&&";
        case OP_OR:
            return "||";
        case OP_COMA:
            return ",";
    }
}

void OpExpr::accept(Visitor& v)
{
    v(*this);
}

void OpExpr::accept(ConstVisitor& v) const
{
    v(*this);
}

std::string ast::op_to_str(OpExpr::Op op)
{
    switch (op)
    {
        case OpExpr::Op::OP_PLUS:
            return "+";
        case OpExpr::Op::OP_MINUS:
            return "-";
        case OpExpr::Op::OP_MUL:
            return "*";
        case OpExpr::Op::OP_DIV:
            return "/";
        case OpExpr::Op::OP_MOD:
            return "%";
        case OpExpr::Op::OP_LSHIFT:
            return "<<";
        case OpExpr::Op::OP_RSHIFT:
            return ">>";
        case OpExpr::Op::OP_GT:
            return ">";
        case OpExpr::Op::OP_GE:
            return ">=";
        case OpExpr::Op::OP_LT:
            return "<";
        case OpExpr::Op::OP_LE:
            return "<=";
        case OpExpr::Op::OP_EQ:
            return "==";
        case OpExpr::Op::OP_DIFF:
            return "!=";
        case OpExpr::Op::OP_BAND:
            return "&";
        case OpExpr::Op::OP_XOR:
            return "^";
        case OpExpr::Op::OP_BOR:
            return "|";
        case OpExpr::Op::OP_AND:
            return "&&";
        case OpExpr::Op::OP_OR:
            return "||";
        case OpExpr::Op::OP_COMA:
            return ",";
    }
}
