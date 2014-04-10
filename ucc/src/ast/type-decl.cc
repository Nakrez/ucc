#include <ast/type-decl.hh>
#include <ast/type.hh>

using namespace ucc;
using namespace ast;

TypeDecl::TypeDecl(const ucc::parse::location& loc,
                   const ucc::misc::Symbol& name,
                   Type* type)
    : Decl(loc, name)
    , type_(type)
{}

TypeDecl::~TypeDecl()
{
    delete type_;
}

const Type* TypeDecl::type_get() const
{
    return type_;
}

Type* TypeDecl::type_get()
{
    return type_;
}

void TypeDecl::accept(Visitor& v)
{
    v(*this);
}

void TypeDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
