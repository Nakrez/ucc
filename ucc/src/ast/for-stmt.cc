#include <ast/for-stmt.hh>

using namespace ucc;
using namespace ast;

ForStmt::ForStmt(const ucc::parse::location& loc,
                 Expr* init,
                 Expr* cond,
                 Expr* inc,
                 Stmt* body)
    : Stmt(loc)
    , init_(init)
    , cond_(cond)
    , inc_(inc)
    , body_(body)
{}

ForStmt::~ForStmt()
{
    delete init_;
    delete cond_;
    delete inc_;
    delete body_;
}

const Expr* ForStmt::init_get() const
{
    return init_;
}

Expr* ForStmt::init_get()
{
    return init_;
}

const Expr* ForStmt::cond_get() const
{
    return cond_;
}

Expr* ForStmt::cond_get()
{
    return cond_;
}

const Expr* ForStmt::inc_get() const
{
    return inc_;
}

Expr* ForStmt::inc_get()
{
    return inc_;
}

const Stmt* ForStmt::body_get() const
{
    return body_;
}

Stmt* ForStmt::body_get()
{
    return body_;
}

void ForStmt::accept(Visitor& v)
{
    v(*this);
}

void ForStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
