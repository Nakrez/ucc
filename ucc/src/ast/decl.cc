#include <ast/decl.hh>

using namespace ucc;
using namespace ast;

Decl::Decl(const ucc::parse::location& loc,
           const ucc::misc::Symbol& name)
    : Ast(loc)
    , name_(name)
{}

Decl::~Decl()
{}

const ucc::misc::Symbol& Decl::name_get() const
{
    return name_;
}

ucc::misc::Symbol& Decl::name_get()
{
    return name_;
}
