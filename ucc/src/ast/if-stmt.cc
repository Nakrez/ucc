#include <ast/if-stmt.hh>
#include <ast/expr.hh>

using namespace ucc;
using namespace ast;

IfStmt::IfStmt(const ucc::parse::location& loc,
               Expr* cond,
               Stmt* if_body,
               Stmt* else_body)
    : Stmt(loc)
    , cond_(cond)
    , if_(if_body)
    , else_(else_body)
{}

IfStmt::~IfStmt()
{
    delete cond_;
    delete if_;
    delete else_;
}

const Expr* IfStmt::cond_get() const
{
    return cond_;
}

Expr* IfStmt::cond_get()
{
    return cond_;
}

const Stmt* IfStmt::if_body_get() const
{
    return if_;
}

Stmt* IfStmt::if_body_get()
{
    return if_;
}

const Stmt* IfStmt::else_body_get() const
{
    return else_;
}

Stmt* IfStmt::else_body_get()
{
    return else_;
}

void IfStmt::accept(Visitor& v)
{
    v(*this);
}

void IfStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
