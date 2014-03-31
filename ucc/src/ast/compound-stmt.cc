#include <ast/all.hh>

using namespace ucc;
using namespace ast;

CompoundStmt::CompoundStmt(const ucc::parse::location& loc,
                           AstList* compound)
    : Stmt(loc)
    , compound_(compound)
{}

CompoundStmt::~CompoundStmt()
{
    delete compound_;
}

const AstList* CompoundStmt::compound_get() const
{
    return compound_;
}

AstList* CompoundStmt::compound_get()
{
    return compound_;
}

void CompoundStmt::accept(Visitor& v)
{
    v(*this);
}

void CompoundStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
