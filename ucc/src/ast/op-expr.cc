#include <ast/op-expr.hh>

using namespace ucc;
using namespace ast;

OpExpr::OpExpr(const ucc::parse::location& loc,
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
