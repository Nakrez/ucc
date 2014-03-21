#include <ast/function-decl.hh>
#include <ast/function-type.hh>

using namespace ucc;
using namespace ast;

FunctionDecl::FunctionDecl(const ucc::parse::location& loc,
                           const ucc::misc::Symbol& name,
                           FunctionType* type)
    : Decl(loc, name)
    , type_(type)
{}

FunctionDecl::~FunctionDecl()
{
    delete type_;
}

const Type* FunctionDecl::return_type_get() const
{
    return type_->return_type_get();
}

Type* FunctionDecl::return_type_get()
{
    return type_->return_type_get();
}

const std::list<VarDecl*>& FunctionDecl::param_get() const
{
    return type_->param_get();
}

std::list<VarDecl*>& FunctionDecl::param_get()
{
    return type_->param_get();
}

void FunctionDecl::return_type_set(Type* t)
{
    type_->return_type_set(t);
}

void FunctionDecl::accept(Visitor& v)
{
    v(*this);
}

void FunctionDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
