#include <ast/sizeof-expr.hh>

using namespace ucc;
using namespace ast;

SizeofExpr::SizeofExpr(const ucc::parse::location& loc,
                       Expr* expr)
    : Expr(loc)
    , expr_(expr)
    , type_(nullptr)
{}

SizeofExpr::SizeofExpr(const ucc::parse::location& loc,
                       Type* type)
    : Expr(loc)
    , expr_(nullptr)
    , type_(type)
{}

SizeofExpr::~SizeofExpr()
{
    delete expr_;
    delete type_;
}

const Expr* SizeofExpr::expr_get() const
{
    return expr_;
}

Expr* SizeofExpr::expr_get()
{
    return expr_;
}

const Type* SizeofExpr::type_get() const
{
    return type_;
}

Type* SizeofExpr::type_get()
{
    return type_;
}

void SizeofExpr::accept(Visitor& v)
{
    v(*this);
}

void SizeofExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
