#include <ast/var-decl.hh>
#include <ast/function-type.hh>

using namespace ucc;
using namespace ast;

FunctionType::FunctionType(const ucc::parse::location& loc)
    : Type(loc)
    , return_type_(nullptr)
    , param_()
{}

FunctionType::FunctionType(const ucc::parse::location& loc,
                           const std::list<VarDecl*>& param)
    : Type(loc)
    , return_type_(nullptr)
    , param_(param)
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

const std::list<VarDecl*>& FunctionType::param_get() const
{
    return param_;
}

std::list<VarDecl*>& FunctionType::param_get()
{
    return param_;
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
