#include <ast/continue-stmt.hh>

using namespace ucc;
using namespace ast;

ContinueStmt::ContinueStmt(const ucc::parse::location& loc)
    : Stmt(loc)
{}

ContinueStmt::~ContinueStmt()
{}

void ContinueStmt::accept(Visitor& v)
{
    v(*this);
}

void ContinueStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
