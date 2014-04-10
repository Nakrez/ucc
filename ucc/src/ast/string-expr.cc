#include <ast/string-expr.hh>

using namespace ucc;
using namespace ast;

StringExpr::StringExpr(const ucc::parse::location& loc, std::string* str)
    : Expr(loc)
    , str_(str)
{}

StringExpr::~StringExpr()
{
    delete str_;
}

std::string* StringExpr::str_get()
{
    return str_;
}

const std::string* StringExpr::str_get() const
{
    return str_;
}

void StringExpr::accept(Visitor& v)
{
    v(*this);
}

void StringExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
