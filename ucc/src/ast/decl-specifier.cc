#include <ast/decl-specifier.hh>
#include <ast/type.hh>
#include <ast/named-type.hh>

using namespace ucc;
using namespace ast;

DeclSpecifier::DeclSpecifier(const ucc::parse::location& loc)
    : loc_(loc)
    , storage_class_(SCS_unspecified)
    , type_qualifier_(TQ_unspecified)
    , function_specifier_(FS_unspecified)
    , type_specifier_(TS_unspecified)
{}

DeclSpecifier::~DeclSpecifier()
{}

bool DeclSpecifier::is_typedef() const
{
    return storage_class_ & SCS_typedef;
}

DeclSpecifier::StorageClassSpecifier DeclSpecifier::storage_class_get() const
{
    return storage_class_;
}

Type* DeclSpecifier::type_get()
{
    Type* t = nullptr;

    if (type_specifier_ & TS_void)
        t = new NamedType(loc_, "void");
    else if (type_specifier_ & TS_char)
        t = new NamedType(loc_, "char");
    else if (type_specifier_ & TS_int)
        t = new NamedType(loc_, "int");
    else if (type_specifier_ & TS_long)
        t = new NamedType(loc_, "long");
    else if (type_specifier_ & TS_float)
        t = new NamedType(loc_, "float");
    else if (type_specifier_ & TS_double)
        t = new NamedType(loc_, "double");

    if (!t)
        t = new NamedType(loc_, "int");

    if (type_qualifier_ & TQ_const)
        t->const_set();
    if (type_qualifier_ & TQ_volatile)
        t->volatile_set();
    if (type_specifier_ & TS_signed)
        t->unsigned_set();

    return t;
}

bool DeclSpecifier::storage_class_set(const StorageClassSpecifier& spec,
                                      ucc::misc::Error& err)
{
    if (spec == SCS_unspecified)
        return true;

    if (storage_class_ != spec &&
        storage_class_ != SCS_unspecified)
        return false;

    storage_class_ = spec;

    return true;
}

bool DeclSpecifier::type_qualifier_set(const TypeQualifier& qual,
                                       ucc::misc::Error&)
{
    if (qual == TQ_unspecified)
        return true;

    if ((type_specifier_ & qual) &&
        type_specifier_ != TQ_unspecified)
        return false;

    type_qualifier_ |= qual;

    return true;
}

bool DeclSpecifier::function_specifier_set(const FunctionSpecifier& spec,
                                           ucc::misc::Error&)
{
    if (spec == FS_unspecified)
        return true;

    if (function_specifier_ != FS_unspecified)
        return false;

    function_specifier_ = FS_inline;

    return true;
}

bool DeclSpecifier::type_specifier_set(const TypeSpecifier& spec,
                                       ucc::misc::Error&)
{
    if (spec == TS_unspecified)
        return true;

    if (type_specifier_ == TS_unspecified)
    {
        type_specifier_ = spec;

        return true;
    }

    if (spec == TS_unsigned && (type_specifier_ & TS_signed))
        return false;

    if (spec == TS_signed && (type_specifier_ & TS_unsigned))
        return false;

    /* XXX: Handle other cases */

    type_specifier_ |= spec;

    return true;
}

bool DeclSpecifier::merge(const DeclSpecifier* decl, ucc::misc::Error& err)
{
    if (!decl)
        return true;

    if (!storage_class_set(decl->storage_class_, err) ||
        !function_specifier_set(decl->function_specifier_, err))
        return false;

    for (unsigned tq = TQ_const; tq <= TQ_const; tq *= 2)
    {
        if (decl->type_qualifier_ & tq)
           if (!type_qualifier_set(static_cast<TypeQualifier>(tq), err))
               return false;
    }

    for (unsigned ts = TS_void; ts <= TS_long_long; ts *= 2)
    {
        if (decl->type_specifier_ & ts)
           if (!type_specifier_set(static_cast<TypeSpecifier>(ts), err))
               return false;
    }

    return true;
}
