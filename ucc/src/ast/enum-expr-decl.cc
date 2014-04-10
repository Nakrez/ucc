#include <ast/enum-expr-decl.hh>

using namespace ucc;
using namespace ast;

EnumExprDecl::EnumExprDecl(const ucc::parse::location& loc,
                           const ucc::misc::Symbol& name,
                           Expr* value)
    : Decl(loc, name)
    , value_(value)
{}

EnumExprDecl::~EnumExprDecl()
{
    delete value_;
}

const Expr* EnumExprDecl::value_get() const
{
    return value_;
}

Expr* EnumExprDecl::value_get()
{
    return value_;
}

void EnumExprDecl::value_set(Expr* e)
{
    value_ = e;
}

void EnumExprDecl::accept(Visitor& v)
{
    v(*this);
}

void EnumExprDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
