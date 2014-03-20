#include <ast/stmt.hh>

using namespace ucc;
using namespace ast;

Stmt::Stmt(const ucc::parse::location& loc)
    : Ast(loc)
{}

Stmt::~Stmt()
{}
