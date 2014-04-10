#include <ast/enum-expr.hh>

using namespace ucc;
using namespace ast;

EnumExpr::EnumExpr(const ucc::parse::location& loc,
                   const ucc::misc::Symbol& name)
    : Expr(loc)
    , name_(name)
{}

EnumExpr::~EnumExpr()
{}

const ucc::misc::Symbol& EnumExpr::name_get() const
{
    return name_;
}

ucc::misc::Symbol& EnumExpr::name_get()
{
    return name_;
}

void EnumExpr::accept(Visitor& v)
{
    v(*this);
}

void EnumExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
