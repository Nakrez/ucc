#include <ast/type.hh>

using namespace ucc;
using namespace ast;

Type::Type(const ucc::parse::location& loc)
    : Ast(loc)
    , is_const_(false)
    , is_volatile_(false)
    , is_restrict_(false)
    , is_unsigned_(false)
{}

Type::~Type()
{}

bool Type::is_const() const
{
    return is_const_;
}

bool Type::is_volatile() const
{
    return is_volatile_;
}

bool Type::is_restrict() const
{
    return is_restrict_;
}

bool Type::is_unsigned() const
{
    return is_unsigned_;
}

void Type::const_set(bool b)
{
    is_const_ = b;
}

void Type::volatile_set(bool b)
{
    is_volatile_ = b;
}

void Type::restrict_set(bool b)
{
    is_restrict_ = b;
}

void Type::unsigned_set(bool b)
{
    is_unsigned_ = b;
}
