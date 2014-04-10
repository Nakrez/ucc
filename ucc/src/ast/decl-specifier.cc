#include <ast/decl-specifier.hh>
#include <ast/type.hh>
#include <ast/named-type.hh>
#include <ast/record-decl.hh>
#include <ast/record-type.hh>
#include <ast/enum-decl.hh>
#include <ast/enum-type.hh>

using namespace ucc;
using namespace ast;

DeclSpecifier::DeclSpecifier(const ucc::parse::location& loc)
    : loc_(loc)
    , storage_class_(SCS_unspecified)
    , type_qualifier_(TQ_unspecified)
    , function_specifier_(FS_unspecified)
    , type_specifier_(TS_unspecified)
    , type_name_("")
    , decl_(nullptr)
{}

DeclSpecifier::~DeclSpecifier()
{}

bool DeclSpecifier::is_typedef() const
{
    return storage_class_ & SCS_typedef;
}

bool DeclSpecifier::is_const() const
{
    return type_qualifier_ & TQ_const;
}

bool DeclSpecifier::is_restrict() const
{
    return type_qualifier_ & TQ_restrict;
}

bool DeclSpecifier::is_volatile() const
{
    return type_qualifier_ & TQ_volatile;
}

bool DeclSpecifier::is_struct_or_union() const
{
    return (type_specifier_ & TS_union) ||
           (type_specifier_ & TS_struct);
}

bool DeclSpecifier::is_struct() const
{
    return type_specifier_ & TS_struct;
}

bool DeclSpecifier::is_union() const
{
    return type_specifier_ & TS_union;
}

bool DeclSpecifier::is_enum() const
{
    return type_specifier_ & TS_enum;
}

ucc::misc::Symbol& DeclSpecifier::name_get()
{
    return type_name_;
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
    else if (type_specifier_ & TS_long_long)
        t = new NamedType(loc_, "long long");
    else if (type_specifier_ & TS_float)
        t = new NamedType(loc_, "float");
    else if (type_specifier_ & TS_double)
        t = new NamedType(loc_, "double");
    else if (type_specifier_ & TS_type_name)
        t = new NamedType(loc_, type_name_);
    else if (type_specifier_ & TS_struct)
    {
        RecordType* rec = new RecordType(loc_, RecordDecl::RecordType::STRUCT,
                                         type_name_);

        rec->def_set(dynamic_cast<RecordDecl*> (decl_));

        t = rec;
    }
    else if (type_specifier_ & TS_union)
    {
        RecordType* rec = new RecordType(loc_, RecordDecl::RecordType::UNION,
                                         type_name_);

        rec->def_set(dynamic_cast<RecordDecl*> (decl_));

        t = rec;
    }
    else if (type_specifier_ & TS_enum)
    {
        EnumType* e = new EnumType(loc_, type_name_);

        e->def_set(dynamic_cast<EnumDecl*> (decl_));

        t = e;
    }

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
    {
        err << misc::Error::Type::parse
            << loc_ << ": error: cannot combine with previous '"
            << storage_class_to_str(storage_class_) << "' declaration";
        return false;
    }

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

    if (spec == TS_long && (type_specifier_ & TS_long))
        type_specifier_ = TS_long_long;
    else
        type_specifier_ |= spec;

    return true;
}

void DeclSpecifier::type_name_set(const ucc::misc::Symbol& s)
{
    type_name_ = s;
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

    type_name_ = decl->type_name_;
    decl_ = decl->decl_;

    return true;
}

Decl* DeclSpecifier::decl_get() const
{
    return decl_;
}

void DeclSpecifier::decl_set(Decl* rec)
{
    decl_ = rec;
}

std::string
DeclSpecifier::storage_class_to_str(StorageClassSpecifier spec) const
{
    switch (spec)
    {
        case SCS_typedef:
            return "typedef";
        case SCS_extern:
            return "extern";
        case SCS_static:
            return "static";
        case SCS_auto:
            return "auto";
        case SCS_register:
            return "register";
        default:
            return "unknown";
    }
}
