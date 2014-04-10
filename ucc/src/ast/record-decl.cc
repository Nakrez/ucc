#include <ast/all.hh>

using namespace ucc;
using namespace ast;

RecordDecl::RecordDecl(const ucc::parse::location& loc,
                       const ucc::misc::Symbol& name,
                       RecordType type,
                       FieldList* fields)
    : Decl(loc, name)
    , type_(type)
    , fields_(fields)
{}

RecordDecl::~RecordDecl()
{
    delete fields_;
}

RecordDecl::RecordType RecordDecl::type_get() const
{
    return type_;
}

const FieldList* RecordDecl::fields_get() const
{
    return fields_;
}

FieldList* RecordDecl::fields_get()
{
    return fields_;
}

void RecordDecl::accept(Visitor& v)
{
    v(*this);
}

void RecordDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
