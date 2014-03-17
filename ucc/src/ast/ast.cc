#include <ast/ast.hh>

using namespace ucc;
using namespace ast;

Ast::Ast(const ucc::parse::location& loc)
    : loc_(loc)
{}

Ast::~Ast()
{}
