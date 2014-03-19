#include <ast/declarator.hh>

using namespace ucc;
using namespace ast;

Declarator::Declarator(const ucc::parse::location& loc,
                       const ucc::misc::Symbol& s)
    : Decl(loc)
    , identifier_(s)
{}

Declarator::~Declarator()
{}

const ucc::misc::Symbol& Declarator::identifier_get() const
{
    return identifier_;
}

void Declarator::accept(Visitor& v)
{
    v(*this);
}

void Declarator::accept(ConstVisitor& v) const
{
    v(*this);
}
