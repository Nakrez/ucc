#include <ast/switch-stmt.hh>
#include <ast/expr.hh>

using namespace ucc;
using namespace ast;

SwitchStmt::SwitchStmt(const ucc::parse::location& loc,
                       Expr* cond,
                       Stmt* body)
    : Stmt(loc)
    , cond_(cond)
    , body_(body)
{}

SwitchStmt::~SwitchStmt()
{
    delete cond_;
    delete body_;
}

const Expr* SwitchStmt::cond_get() const
{
    return cond_;
}

Expr* SwitchStmt::cond_get()
{
    return cond_;
}

const Stmt* SwitchStmt::body_get() const
{
    return body_;
}

Stmt* SwitchStmt::body_get()
{
    return body_;
}

void SwitchStmt::accept(Visitor& v)
{
    v(*this);
}

void SwitchStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
