#include <ast/enum-decl.hh>
#include <ast/all.hh>

using namespace ucc;
using namespace ast;

EnumDecl::EnumDecl(const ucc::parse::location& loc,
                   const ucc::misc::Symbol& name,
                   EnumExprList* body)
    : Decl(loc, name)
    , body_(body)
{}

EnumDecl::~EnumDecl()
{
    delete body_;
}

const EnumExprList* EnumDecl::body_get() const
{
    return body_;
}

EnumExprList* EnumDecl::body_get()
{
    return body_;
}

void EnumDecl::accept(Visitor& v)
{
    v(*this);
}

void EnumDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
