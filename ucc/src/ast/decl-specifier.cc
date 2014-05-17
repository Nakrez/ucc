/*
Copyright (C) 2014 Baptiste Covolato <b.covolato@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <misc/diagnostic-reporter.hh>
#include <ast/decl-specifier.hh>
#include <ast/ty.hh>
#include <ast/named-ty.hh>
#include <ast/record-decl.hh>
#include <ast/record-ty.hh>
#include <ast/enum-decl.hh>
#include <ast/enum-ty.hh>

using namespace ucc;
using namespace ast;

DeclSpecifier::DeclSpecifier(const ucmp::misc::location& loc)
    : loc_(loc)
    , storage_class_(SCS_unspecified)
    , type_qualifier_(TQ_unspecified)
    , function_specifier_(FS_unspecified)
    , type_specifier_(TS_unspecified)
    , type_name_("")
    , decl_(nullptr)
{}

Ty* DeclSpecifier::ty_get()
{
    Ty* t = nullptr;

    if (type_specifier_ & TS_type_name)
        t = new NamedTy(loc_, type_name_);
    else if (type_specifier_ & TS_struct)
    {
        RecordTy* rec = new RecordTy(loc_, RecordDecl::RecordType::STRUCT,
                                     type_name_);

        rec->def_set(dynamic_cast<RecordDecl*> (decl_));

        t = rec;
    }
    else if (type_specifier_ & TS_union)
    {
        RecordTy* rec = new RecordTy(loc_, RecordDecl::RecordType::UNION,
                                     type_name_);

        rec->def_set(dynamic_cast<RecordDecl*> (decl_));

        t = rec;
    }
    else if (type_specifier_ & TS_enum)
    {
        EnumTy* e = new EnumTy(loc_, type_name_);

        e->def_set(dynamic_cast<EnumDecl*> (decl_));

        t = e;
    }
    else
        t = new NamedTy(loc_, type_to_string());

    if (type_qualifier_ & TQ_const)
        t->const_set();
    if (type_qualifier_ & TQ_volatile)
        t->volatile_set();
    if (type_specifier_ & TS_signed)
        t->unsigned_set();

    return t;
}

bool DeclSpecifier::storage_class_set(const StorageClassSpecifier& spec)
{
    if (spec == SCS_unspecified)
        return true;

    if (storage_class_ != spec &&
        storage_class_ != SCS_unspecified)
    {
        ucmp::misc::Diagnostic d;

        d << ucmp::misc::Diagnostic::Severity::err
          << ucmp::misc::Diagnostic::Type::parse << loc_
          << "cannot combine with previous '"
          << storage_class_to_str(storage_class_) << "' declaration";

        ucmp::misc::DiagnosticReporter::instance_get().add(d);

        return false;
    }

    storage_class_ = spec;

    return true;
}

bool DeclSpecifier::type_qualifier_set(const TypeQualifier& qual)
{
    if (qual == TQ_unspecified)
        return true;

    if ((type_specifier_ & qual) &&
        type_specifier_ != TQ_unspecified)
        return false;

    type_qualifier_ |= qual;

    return true;
}

bool DeclSpecifier::function_specifier_set(const FunctionSpecifier& spec)
{
    if (spec == FS_unspecified)
        return true;

    if (function_specifier_ != FS_unspecified)
        return false;

    function_specifier_ = FS_inline;

    return true;
}

bool DeclSpecifier::type_specifier_set(const TypeSpecifier& spec)
{
    if (spec == TS_unspecified)
        return true;

    if (type_specifier_ == TS_unspecified)
    {
        type_specifier_ = spec;

        return true;
    }

    /* Combination of signed and unsigned */
    if (spec & TS_unsigned && (type_specifier_ & TS_signed))
    {
        ucmp::misc::Diagnostic d;

        d << ucmp::misc::Diagnostic::Severity::err
          << ucmp::misc::Diagnostic::Type::parse
          << loc_ << "type cannot be signed and unsigned";

        ucmp::misc::DiagnosticReporter::instance_get().add(d);

        return false;
    }

    if (spec & TS_signed && (type_specifier_ & TS_unsigned))
    {
        ucmp::misc::Diagnostic d;

        d << ucmp::misc::Diagnostic::Severity::err
          << ucmp::misc::Diagnostic::Type::parse
          << loc_ << "type cannot be signed and unsigned";

        ucmp::misc::DiagnosticReporter::instance_get().add(d);

        return false;
    }

    /* Float/double cannot be unsigned */
    if ((type_specifier_ & TS_signed || type_specifier_ & TS_unsigned) &&
        (spec == TS_double || spec == TS_float))
    {
        ucmp::misc::Diagnostic d;

        d << ucmp::misc::Diagnostic::Severity::err
          << ucmp::misc::Diagnostic::Type::parse
          << loc_ << "float and double cannot be signed or unsigned";

        ucmp::misc::DiagnosticReporter::instance_get().add(d);

        return false;
    }

    /* Multiple types */
    if (spec == TS_long && (type_specifier_ & TS_long))
        type_specifier_ = TS_long_long;
    else if (spec == TS_double && (type_specifier_ & TS_long))
        type_specifier_ |= TS_double;
    else if (spec == TS_int && (type_specifier_ & TS_long))
    {
        type_specifier_ &= TS_int;
        type_specifier_ |= TS_long;
    }
    else if (spec != TS_signed && spec != TS_unsigned &&
        (type_specifier_ & ~(TS_signed + TS_unsigned)) != TS_unspecified)
    {
        ucmp::misc::Diagnostic d;

        d << ucmp::misc::Diagnostic::Severity::err
          << ucmp::misc::Diagnostic::Type::parse
          << loc_ << "wrong type combination";

        ucmp::misc::DiagnosticReporter::instance_get().add(d);

        return false;
    }
    else
        type_specifier_ |= spec;

    return true;
}

void DeclSpecifier::type_name_set(const ucmp::misc::Symbol& s)
{
    type_name_ = s;
}

bool DeclSpecifier::merge(const DeclSpecifier* decl)
{
    if (!decl)
        return true;

    if (!storage_class_set(decl->storage_class_) ||
        !function_specifier_set(decl->function_specifier_))
        return false;

    for (unsigned tq = TQ_const; tq <= TQ_const; tq *= 2)
    {
        if (decl->type_qualifier_ & tq)
           if (!type_qualifier_set(static_cast<TypeQualifier>(tq)))
               return false;
    }

    for (unsigned ts = TS_void; ts <= TS_long_long; ts *= 2)
    {
        if (decl->type_specifier_ & ts)
           if (!type_specifier_set(static_cast<TypeSpecifier>(ts)))
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

std::string DeclSpecifier::type_to_string() const
{
    std::string ret = "";

    if (type_specifier_ & TS_unsigned)
        ret = "unsigned ";
    else if (type_specifier_ & TS_signed)
        ret = "signed ";

    if (type_specifier_ == TS_void)
        ret += "void";
    else if ((type_specifier_ & TS_long) && (type_specifier_ & TS_double))
        ret += "long double";
    else if (type_specifier_ & TS_char)
        ret += "char";
    else if (type_specifier_ & TS_short)
        ret += "short";
    else if (type_specifier_ & TS_long)
        ret += "long";
    else if (type_specifier_ & TS_float)
        ret += "float";
    else if (type_specifier_ & TS_double)
        ret += "double";
    else if (type_specifier_ & TS_long_long)
        ret += "long long";
    else
        ret += "int";

    return ret;
}
