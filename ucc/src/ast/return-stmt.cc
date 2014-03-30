#include <ast/return-stmt.hh>

using namespace ucc;
using namespace ast;

ReturnStmt::ReturnStmt(const ucc::parse::location& loc)
    : Stmt(loc)
    , expr_(nullptr)
{}

ReturnStmt::ReturnStmt(const ucc::parse::location& loc, Expr* expr)
    : Stmt(loc)
    , expr_(expr)
{}

ReturnStmt::~ReturnStmt()
{
    delete expr_;
}

Expr* ReturnStmt::expr_get()
{
    return expr_;
}

const Expr* ReturnStmt::expr_get() const
{
    return expr_;
}

void ReturnStmt::accept(Visitor& v)
{
    v(*this);
}

void ReturnStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
