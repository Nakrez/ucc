#include <ast/all.hh>

using namespace ucc;
using namespace ast;

InitListExpr::InitListExpr(const ucc::parse::location& loc,
                           ExprList* list)
    : Expr(loc)
    , list_(list)
{}

InitListExpr::~InitListExpr()
{
    delete list_;
}

const ExprList* InitListExpr::list_get() const
{
    return list_;
}

ExprList* InitListExpr::list_get()
{
    return list_;
}

void InitListExpr::accept(Visitor& v)
{
    v(*this);
}

void InitListExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
