#include <ast/field-decl.hh>

using namespace ucc;
using namespace ast;

FieldDecl::FieldDecl(const ucc::parse::location& loc,
                     const ucc::misc::Symbol& name,
                     Type* type,
                     Expr* bit_field)
    : Decl(loc, name)
    , type_(type)
    , bit_field_(bit_field)
{}

FieldDecl::~FieldDecl()
{
    delete type_;
    delete bit_field_;
}

const Type* FieldDecl::type_get() const
{
    return type_;
}

Type* FieldDecl::type_get()
{
    return type_;
}

const Expr* FieldDecl::bit_field_get() const
{
    return bit_field_;
}

Expr* FieldDecl::bit_field_get()
{
    return bit_field_;
}

void FieldDecl::type_set(Type* t)
{
    type_ = t;
}

void FieldDecl::accept(Visitor& v)
{
    v(*this);
}

void FieldDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
