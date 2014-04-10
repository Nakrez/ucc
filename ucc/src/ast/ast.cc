#include <ast/ast.hh>

using namespace ucc;
using namespace ast;

Ast::Ast(const ucc::parse::location& loc)
    : loc_(loc)
{}

Ast::~Ast()
{}

const ucc::parse::location& Ast::location_get() const
{
    return loc_;
}

ucc::parse::location& Ast::location_get()
{
    return loc_;
}
