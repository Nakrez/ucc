#include <ast/declarator.hh>
#include <ast/type.hh>
#include <ast/expr.hh>

using namespace ucc;
using namespace ast;

Declarator::Declarator(const ucc::parse::location& loc,
                       const ucc::misc::Symbol& s)
    : Decl(loc, s)
    , type_(nullptr)
    , init_(nullptr)
{}

Declarator::~Declarator()
{
    /* type_ and init_ is not deleted because it is transfered to a decl */
}

const Type* Declarator::type_get() const
{
    return type_;
}

Type* Declarator::type_get()
{
    return type_;
}

const Expr* Declarator::init_get() const
{
    return init_;
}

Expr* Declarator::init_get()
{
    return init_;
}

void Declarator::init_set(Expr* e)
{
    init_ = e;
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
