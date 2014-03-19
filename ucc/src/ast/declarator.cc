#include <ast/declarator.hh>

using namespace ucc;
using namespace ast;

Declarator::Declarator(const ucc::parse::location& loc,
                       const ucc::misc::Symbol& s)
    : Decl(loc)
    , identifier_(s)
    , type_(nullptr)
{}

Declarator::~Declarator()
{
    delete type_;
}

const ucc::misc::Symbol& Declarator::identifier_get() const
{
    return identifier_;
}

const Type* Declarator::type_get() const
{
    return type_;
}

bool Declarator::extends_type(Type* t)
{
    if (!type_)
    {
        type_ = t;

        return true;
    }

    return type_->extends_type(t);
}

void Declarator::accept(Visitor& v)
{
    v(*this);
}

void Declarator::accept(ConstVisitor& v) const
{
    v(*this);
}
