#include <ast/default-stmt.hh>

using namespace ucc;
using namespace ast;

DefaultStmt::DefaultStmt(const ucc::parse::location& loc, Stmt* body)
    : Stmt(loc)
    , body_(body)
{}

DefaultStmt::~DefaultStmt()
{
    delete body_;
}

const Stmt* DefaultStmt::body_get() const
{
    return body_;
}

Stmt* DefaultStmt::body_get()
{
    return body_;
}

void DefaultStmt::accept(Visitor& v)
{
    v(*this);
}

void DefaultStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
