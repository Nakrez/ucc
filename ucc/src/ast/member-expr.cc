#include <ast/member-expr.hh>

using namespace ucc;
using namespace ast;

MemberExpr::MemberExpr(const ucc::parse::location& loc,
                       Expr* lexpr,
                       const ucc::misc::Symbol& name,
                       bool is_arrow)
    : Expr(loc)
    , lexpr_(lexpr)
    , name_(name)
    , is_arrow_(is_arrow)
{}

MemberExpr::~MemberExpr()
{
    delete lexpr_;
}

const Expr* MemberExpr::lexpr_get() const
{
    return lexpr_;
}

Expr* MemberExpr::lexpr_get()
{
    return lexpr_;
}

const ucc::misc::Symbol& MemberExpr::name_get() const
{
    return name_;
}

ucc::misc::Symbol& MemberExpr::name_get()
{
    return name_;
}

bool MemberExpr::is_arrow() const
{
    return is_arrow_;
}

void MemberExpr::accept(Visitor& v)
{
    v(*this);
}

void MemberExpr::accept(ConstVisitor& v) const
{
    v(*this);
}
