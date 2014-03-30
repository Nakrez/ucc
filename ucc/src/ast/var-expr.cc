#include <ast/var-expr.hh>

using namespace ucc;
using namespace ast;

VarExpr::VarExpr(const ucc::parse::location& loc,
                 const ucc::misc::Symbol& sym)
    : Expr(loc)
    , name_(sym)
{}

VarExpr::~VarExpr()
{}

const misc::Symbol& VarExpr::name_get() const
{
    return name_;
}

misc::Symbol& VarExpr::name_get()
{
    return name_;
}

void VarExpr::accept(Visitor& v)
{
    v(*this);
}

void VarExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
