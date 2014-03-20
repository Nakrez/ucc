#include <ast/function-type.hh>

using namespace ucc;
using namespace ast;

FunctionType::FunctionType(const ucc::parse::location& loc)
    : Type(loc)
    , return_type_(nullptr)
{}

FunctionType::~FunctionType()
{}

const Type* FunctionType::return_type_get() const
{
    return return_type_;
}

Type* FunctionType::return_type_get()
{
    return return_type_;
}

void FunctionType::return_type_set(Type* t)
{
    return_type_ = t;
}

bool FunctionType::extends_type(Type *)
{
    return false;
}

void FunctionType::accept(Visitor& v)
{
    v(*this);
}

void FunctionType::accept(ConstVisitor& v) const
{
    v(*this);
}
