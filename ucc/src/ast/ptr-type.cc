#include <ast/ptr-type.hh>

using namespace ucc;
using namespace ast;

PtrType::PtrType(const ucc::parse::location& loc)
    : Type(loc)
    , pointed_type_(nullptr)
{}

PtrType::PtrType(const ucc::parse::location& loc, Type* pointed_type)
    : Type(loc)
    , pointed_type_(pointed_type)
{}

PtrType::~PtrType()
{
    delete pointed_type_;
}

const Type* PtrType::pointed_type_get() const
{
    return pointed_type_;
}
Type* PtrType::pointed_type_get()
{
    return pointed_type_;
}

bool PtrType::extends_type(Type *t)
{
    if (!pointed_type_)
    {
        pointed_type_ = t;
        return true;
    }

    return pointed_type_->extends_type(t);
}

void PtrType::accept(Visitor& v)
{
    v(*this);
}

void PtrType::accept(ConstVisitor& v) const
{
    v(*this);
}
