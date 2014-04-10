# include <ast/do-while-stmt.hh>

using namespace ucc;
using namespace ast;

DoWhileStmt::DoWhileStmt(const ucc::parse::location& loc,
                         Expr* cond,
                         Ast* body)
    : WhileStmt(loc, cond, body)
{}

DoWhileStmt::~DoWhileStmt()
{}

void DoWhileStmt::accept(Visitor& v)
{
    v(*this);
}

void DoWhileStmt::accept(ConstVisitor& v) const
{
    v(*this);
}
