#include <ast/break-stmt.hh>

using namespace ucc;
using namespace ast;

BreakStmt::BreakStmt(const ucc::parse::location& loc)
    : Stmt(loc)
{}

BreakStmt::~BreakStmt()
{}

void BreakStmt::accept(Visitor& v)
{
    v(*this);
}

void BreakStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
