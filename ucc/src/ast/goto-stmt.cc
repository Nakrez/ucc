#include <ast/goto-stmt.hh>

using namespace ucc;
using namespace ast;

GotoStmt::GotoStmt(const ucc::parse::location& loc,
                   const ucc::misc::Symbol& name)
    : Stmt(loc)
    , name_(name)
{}

GotoStmt::~GotoStmt()
{}

const ucc::misc::Symbol& GotoStmt::name_get() const
{
    return name_;
}

ucc::misc::Symbol& GotoStmt::name_get()
{
    return name_;
}

void GotoStmt::accept(Visitor& v)
{
    v(*this);
}

void GotoStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
