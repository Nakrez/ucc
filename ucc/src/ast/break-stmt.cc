#include <ast/break-stmt.hh>

using namespace ucc;
using namespace ast;

BreakStmt::BreakStmt(const ucc::misc::location& loc)
    : Stmt(loc)
    , def_(nullptr)
{}

BreakStmt::~BreakStmt()
{}

const Stmt* BreakStmt::def_get() const
{
    return def_;
}

Stmt* BreakStmt::def_get()
{
    return def_;
}

void BreakStmt::def_set(Stmt* def)
{
    def_ = def;
}

void BreakStmt::accept(Visitor& v)
{
    v(*this);
}

void BreakStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
