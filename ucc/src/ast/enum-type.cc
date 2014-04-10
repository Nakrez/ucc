#include <ast/enum-type.hh>

using namespace ucc;
using namespace ast;

EnumType::EnumType(const ucc::parse::location& loc,
                   const ucc::misc::Symbol& name)
    : Type(loc)
    , name_(name)
    , def_(nullptr)
{}

EnumType::~EnumType()
{}

const ucc::misc::Symbol& EnumType::name_get() const
{
    return name_;
}

ucc::misc::Symbol& EnumType::name_get()
{
    return name_;
}

const EnumDecl* EnumType::def_get() const
{
    return def_;
}

EnumDecl* EnumType::def_get()
{
    return def_;
}

void EnumType::def_set(EnumDecl* def)
{
    def_ = def;
}

void EnumType::accept(Visitor& v)
{
    v(*this);
}

void EnumType::accept(ConstVisitor& v) const
{
    v(*this);
}
