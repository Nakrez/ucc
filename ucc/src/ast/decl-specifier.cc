#include <ast/decl-specifier.hh>

using namespace ucc;
using namespace ast;

DeclSpecifier::DeclSpecifier(const ucc::parse::location& loc)
    : Decl(loc)
    , storage_class_(SCS_unspecified)
    , type_qualifier_(TQ_unspecified)
    , function_specifier_(FS_unspecified)
    , type_specifier_(TS_unspecified)
{}

DeclSpecifier::~DeclSpecifier()
{}

void DeclSpecifier::accept(Visitor& v)
{
    v(*this);
}

void DeclSpecifier::accept(ConstVisitor& v) const
{
    v(*this);
}

bool DeclSpecifier::storage_class_set(const StorageClassSpecifier& spec)
{
    if (spec == StorageClassSpecifier::SCS_unspecified)
        return true;

    if (storage_class_ != spec &&
        storage_class_ != StorageClassSpecifier::SCS_unspecified)
        return false;

    storage_class_ = spec;

    return true;
}

bool DeclSpecifier::type_qualifier_set(const TypeQualifier& qual)
{
    if (qual == TypeQualifier::TQ_unspecified)
        return true;

    if ((type_specifier_ & qual) &&
        type_specifier_ != TypeQualifier::TQ_unspecified)
        return false;

    type_qualifier_ |= qual;

    return true;
}

bool DeclSpecifier::function_specifier_set(const FunctionSpecifier& spec)
{
    if (spec == DeclSpecifier::FS_unspecified)
        return true;

    if (function_specifier_ != FS_unspecified)
        return false;

    function_specifier_ = FS_inline;

    return true;
}

bool DeclSpecifier::type_specifier_set(const TypeSpecifier& spec)
{
    if (spec == TypeSpecifier::TS_unspecified)
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

bool DeclSpecifier::merge(const DeclSpecifier* decl)
{
    if (!decl)
        return true;

    return storage_class_set(decl->storage_class_get()) &&
           type_qualifier_set(decl->type_qualifier_get()) &&
           function_specifier_set(decl->function_specifier_get()) &&
           type_specifier_set(decl->type_specifier_get());
}
