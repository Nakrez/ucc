#include <ast/decl.hh>

using namespace ucc;
using namespace ast;

Decl::Decl(const ucc::parse::location& loc)
    : Ast(loc)
{}

Decl::~Decl()
{}
