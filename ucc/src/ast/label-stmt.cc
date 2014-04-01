#include <ast/label-stmt.hh>

using namespace ucc;
using namespace ast;

LabelStmt::LabelStmt(const ucc::parse::location& loc,
                     const ucc::misc::Symbol& sym,
                     Stmt* stmt)
    : Stmt(loc)
    , name_(sym)
    , stmt_(stmt)
{}

LabelStmt::~LabelStmt()
{
    delete stmt_;
}

const ucc::misc::Symbol& LabelStmt::name_get() const
{
    return name_;
}

ucc::misc::Symbol& LabelStmt::name_get()
{
    return name_;
}

const Stmt* LabelStmt::stmt_get() const
{
    return stmt_;
}

Stmt* LabelStmt::stmt_get()
{
    return stmt_;
}

void LabelStmt::accept(Visitor& v)
{
    v(*this);
}

void LabelStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
