#include <ast/array-type.hh>

using namespace ucc;
using namespace ast;

ArrayType::ArrayType(const ucc::parse::location& loc)
    : Type(loc)
    , sub_type_(nullptr)
    , size_(nullptr)
{}

ArrayType::ArrayType(const ucc::parse::location& loc, Expr* expr)
    : Type(loc)
    , sub_type_(nullptr)
    , size_(expr)
{}

ArrayType::~ArrayType()
{}

const Type* ArrayType::sub_type_get() const
{
    return sub_type_;
}

Type* ArrayType::sub_type_get()
{
    return sub_type_;
}

const Expr* ArrayType::size_get() const
{
    return size_;
}

Expr* ArrayType::size_get()
{
    return size_;
}

bool ArrayType::extends_type(Type *t)
{
    if (sub_type_ == nullptr)
    {
        /*
        if (dynamic_cast<FunctionType*> (t))
        {
            sub_type_ = t;
            return true;
        }
        */

        return false;
    }

    return sub_type_->extends_type(t);
}

void ArrayType::accept(Visitor& v)
{
    v(*this);
}

void ArrayType::accept(ConstVisitor& v) const
{
    v(*this);
}
