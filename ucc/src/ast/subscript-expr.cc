#include <ast/subscript-expr.hh>

using namespace ucc;
using namespace ast;

SubscriptExpr::SubscriptExpr(const ucc::parse::location& loc,
                             Expr* var,
                             Expr* expr)
    : Expr(loc)
    , var_(var)
    , expr_(expr)
{}

SubscriptExpr::~SubscriptExpr()
{
    delete var_;
    delete expr_;
}

const Expr* SubscriptExpr::var_get() const
{
    return var_;
}

Expr* SubscriptExpr::var_get()
{
    return var_;
}

const Expr* SubscriptExpr::expr_get() const
{
    return expr_;
}

Expr* SubscriptExpr::expr_get()
{
    return expr_;
}

void SubscriptExpr::accept(Visitor& v)
{
    v(*this);
}

void SubscriptExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
