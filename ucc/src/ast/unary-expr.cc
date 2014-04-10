#include <ast/unary-expr.hh>

using namespace ucc;
using namespace ast;

UnaryExpr::UnaryExpr(const ucc::parse::location& loc,
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
