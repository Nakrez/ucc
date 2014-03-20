#include <ast/expr.hh>

using namespace ucc;
using namespace ast;

Expr::Expr(const ucc::parse::location& loc)
    : Stmt(loc)
{}

Expr::~Expr()
{}
