#include <ast/all.hh>

using namespace ucc;
using namespace ast;

FunctionDecl::FunctionDecl(const ucc::parse::location& loc,
                           const ucc::misc::Symbol& name,
                           FunctionType* type)
    : Decl(loc, name)
    , type_(type)
    , compound_(nullptr)
{}

FunctionDecl::FunctionDecl(const ucc::parse::location& loc,
                           const ucc::misc::Symbol& name,
                           FunctionType* type,
                           AstList* compound)
    : Decl(loc, name)
    , type_(type)
    , compound_(compound)
{}

FunctionDecl::~FunctionDecl()
{
    delete type_;
    delete compound_;
}

const AstList* FunctionDecl::compound_get() const
{
    return compound_;
}

AstList* FunctionDecl::compound_get()
{
    return compound_;
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
