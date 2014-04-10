#include <ast/float-expr.hh>

using namespace ucc;
using namespace ast;

FloatExpr::FloatExpr(const ucc::parse::location& loc, long double val)
    : Expr(loc)
    , val_(val)
{}

FloatExpr::~FloatExpr()
{}

long double FloatExpr::value_get() const
{
    return val_;
}

void FloatExpr::accept(Visitor& v)
{
    v(*this);
}

void FloatExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
