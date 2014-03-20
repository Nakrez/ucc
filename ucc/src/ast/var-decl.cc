#include <ast/var-decl.hh>

#include <ast/expr.hh>
#include <ast/type.hh>

using namespace ucc;
using namespace ast;

VarDecl::VarDecl(const ucc::parse::location& loc)
    : Decl(loc)
    , type_(nullptr)
    , init_(nullptr)
{}

VarDecl::VarDecl(const ucc::parse::location& loc, Type* type)
    : Decl(loc)
    , type_(type)
    , init_(nullptr)
{}

VarDecl::VarDecl(const ucc::parse::location& loc, Type* type, Expr* e)
    : Decl(loc)
    , type_(type)
    , init_(e)
{}

VarDecl::~VarDecl()
{}

const Type* VarDecl::type_get() const
{
    return type_;
}

Type* VarDecl::type_get()
{
    return type_;
}

const Expr* VarDecl::init_get() const
{
    return init_;
}

Expr* VarDecl::init_get()
{
    return init_;
}

void VarDecl::accept(Visitor& v)
{
    v(*this);
}

void VarDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
