#include <ast/cast-expr.hh>

using namespace ucc;
using namespace ast;

CastExpr::CastExpr(const ucc::parse::location& loc,
                   Type* type,
                   Expr* expr)
    : Expr(loc)
    , type_(type)
    , expr_(expr)
{}

CastExpr::~CastExpr()
{
    delete type_;
    delete expr_;
}

const Type* CastExpr::type_get() const
{
    return type_;
}

Type* CastExpr::type_get()
{
    return type_;
}

const Expr* CastExpr::expr_get() const
{
    return expr_;
}

Expr* CastExpr::expr_get()
{
    return expr_;
}

void CastExpr::accept(Visitor& v)
{
    v(*this);
}

void CastExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
