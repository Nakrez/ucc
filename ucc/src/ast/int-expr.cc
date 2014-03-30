#include <ast/int-expr.hh>

using namespace ucc;
using namespace ast;

IntExpr::IntExpr(const ucc::parse::location& loc, int val)
    : Expr(loc)
    , val_(val)
{}

IntExpr::~IntExpr()
{}

int IntExpr::value_get() const
{
    return val_;
}

void IntExpr::accept(Visitor& v)
{
    v(*this);
}

void IntExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
