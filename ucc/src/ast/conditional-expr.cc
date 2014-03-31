#include <ast/conditional-expr.hh>

using namespace ucc;
using namespace ast;

ConditionalExpr::ConditionalExpr(const ucc::parse::location& loc,
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
