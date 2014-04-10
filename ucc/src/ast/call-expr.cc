#include <ast/all.hh>

using namespace ucc;
using namespace ast;

CallExpr::CallExpr(const ucc::parse::location& loc,
                   Expr* var,
                   ExprList* param)
    : Expr(loc)
    , var_(var)
    , param_(param)
{}

CallExpr::~CallExpr()
{
    delete var_;
    delete param_;
}

const Expr* CallExpr::var_get() const
{
    return var_;
}

Expr* CallExpr::var_get()
{
    return var_;
}

const ExprList* CallExpr::param_get() const
{
    return param_;
}

ExprList* CallExpr::param_get()
{
    return param_;
}

void CallExpr::accept(Visitor& v)
{
    v(*this);
}

void CallExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
