#include <ast/case-stmt.hh>

using namespace ucc;
using namespace ast;

CaseStmt::CaseStmt(const ucc::parse::location& loc,
                   Expr* expr,
                   Stmt* body)
    : Stmt(loc)
    , expr_(expr)
    , body_(body)
{}

CaseStmt::~CaseStmt()
{
    delete expr_;
    delete body_;
}

const Expr* CaseStmt::expr_get() const
{
    return expr_;
}

Expr* CaseStmt::expr_get()
{
    return expr_;
}

const Stmt* CaseStmt::body_get() const
{
    return body_;
}

Stmt* CaseStmt::body_get()
{
    return body_;
}

void CaseStmt::accept(Visitor& v)
{
    v(*this);
}

void CaseStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
