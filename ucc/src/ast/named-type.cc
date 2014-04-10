#include <ast/named-type.hh>

using namespace ucc;
using namespace ast;

NamedType::NamedType(const ucc::parse::location& loc,
                     const ucc::misc::Symbol& name)
    : Type(loc)
    , name_(name)
{}

NamedType::~NamedType()
{}


const ucc::misc::Symbol& NamedType::name_get() const
{
    return name_;
}

ucc::misc::Symbol& NamedType::name_get()
{
    return name_;
}

bool NamedType::extends_type(Type *)
{
    return false;
}

void NamedType::accept(Visitor& v)
{
    v(*this);
}

void NamedType::accept(ConstVisitor& v) const
{
    v(*this);
}
