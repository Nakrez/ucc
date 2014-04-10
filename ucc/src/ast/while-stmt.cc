#include <ast/all.hh>

using namespace ucc;
using namespace ast;

WhileStmt::WhileStmt(const ucc::parse::location& loc, Expr* cond, Ast* body)
    : Stmt(loc)
    , cond_(cond)
    , body_(body)
{}

WhileStmt::~WhileStmt()
{
    delete cond_;
    delete body_;
}

const Expr* WhileStmt::cond_get() const
{
    return cond_;
}

Expr* WhileStmt::cond_get()
{
    return cond_;
}

const Ast* WhileStmt::body_get() const
{
    return body_;
}

Ast* WhileStmt::body_get()
{
    return body_;
}

void WhileStmt::accept(Visitor& v)
{
    v(*this);
}

void WhileStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
