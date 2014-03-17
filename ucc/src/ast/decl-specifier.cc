#include <ast/decl-specifier.hh>

using namespace ucc;
using namespace ast;

DeclSpecifier::DeclSpecifier(const ucc::parse::location& loc)
    : Decl(loc)
    , storage_class_(SCS_unspecified)
    , type_qualifier_(TQ_unspecified)
    , function_specifier_(FS_unspecified)
    , type_specifier_(TS_unspecified)
{}

DeclSpecifier::~DeclSpecifier()
{}

void DeclSpecifier::accept(Visitor& v)
{
    v(*this);
}

void DeclSpecifier::accept(ConstVisitor& v)
{
    v(*this);
}
