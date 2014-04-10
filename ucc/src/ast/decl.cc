#include <ast/decl.hh>

using namespace ucc;
using namespace ast;

Decl::Decl(const ucc::parse::location& loc,
           const ucc::misc::Symbol& name)
    : Ast(loc)
    , name_(name)
    , storage_(DeclSpecifier::StorageClassSpecifier::SCS_unspecified)
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

bool Decl::is_static() const
{
    return storage_ == DeclSpecifier::StorageClassSpecifier::SCS_static;
}

bool Decl::is_extern() const
{
    return storage_ == DeclSpecifier::StorageClassSpecifier::SCS_extern;
}

bool Decl::is_auto() const
{
    return storage_ == DeclSpecifier::StorageClassSpecifier::SCS_auto;
}

bool Decl::is_register() const
{
    return storage_ == DeclSpecifier::StorageClassSpecifier::SCS_register;
}

DeclSpecifier::StorageClassSpecifier Decl::storage_class_get() const
{
    return storage_;
}

void Decl::storage_class_set(DeclSpecifier::StorageClassSpecifier storage)
{
    storage_ = storage;
}
