#include <ast/var-decl.hh>

#include <ast/expr.hh>
#include <ast/type.hh>

using namespace ucc;
using namespace ast;

VarDecl::VarDecl(const ucc::parse::location& loc,
                 const ucc::misc::Symbol& name,
                 Type* type,
                 Expr* e)
    : Decl(loc, name)
    , type_(type)
    , init_(e)
    , is_elipsis_(false)
{}

VarDecl::VarDecl(const ucc::parse::location& loc)
    : Decl(loc, "")
    , type_(nullptr)
    , init_(nullptr)
    , is_elipsis_(true)
{}

VarDecl::~VarDecl()
{
    delete type_;
    delete init_;
}

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

bool VarDecl::is_elipsis() const
{
    return is_elipsis_;
}

void VarDecl::accept(Visitor& v)
{
    v(*this);
}

void VarDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
