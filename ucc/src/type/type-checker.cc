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

#include <cassert>

#include <type/type-checker.hh>
#include <type/builtin-type.hh>
#include <type/ptr.hh>
#include <type/named.hh>
#include <type/const.hh>
#include <type/array.hh>
#include <type/field.hh>
#include <type/record.hh>

using namespace ucc;
using namespace type;

TypeChecker::TypeChecker()
{}

TypeChecker::~TypeChecker()
{}

const Type* TypeChecker::node_type(ast::TypeUser& a)
{
    if (!a.type_get())
        a.accept(*this);

    return a.type_get();
}

void TypeChecker::error(const std::string& msg, const ucc::misc::location& loc)
{
    ucc::misc::Diagnostic d;

    d << ucc::misc::Diagnostic::Severity::err;
    d << ucc::misc::Diagnostic::Type::type << loc;
    d << msg;

    ucc::misc::DiagnosticReporter::instance_get().add(d);
}

void TypeChecker::check_assign_types(const ucc::misc::location& loc,
                                     ast::AssignExpr::AssignOp op,
                                     const Type* t1,
                                     const Type* t2)
{
    Type::TypeCompatibility c;

    c = t1->actual_type().compatible_on_assign(t2->actual_type(), op);

    if (c != Type::TypeCompatibility::full)
    {
        ucc::misc::Diagnostic d;

        if (c == Type::TypeCompatibility::error)
            d << ucc::misc::Diagnostic::Severity::err;
        else
            d << ucc::misc::Diagnostic::Severity::warn;

        d << ucc::misc::Diagnostic::Type::type << loc;
        d << "incompatible assignement between '" << t1->to_str() << "' and '"
          << t2->to_str() << "'";

        ucc::misc::DiagnosticReporter::instance_get().add(d);
    }
}

void TypeChecker::operator()(ast::VarDecl& ast)
{
    const Type* var_type = node_type(*ast.ty_get());

    if (ast.init_get())
    {
        const Type* init_type = node_type(*ast.init_get());

        check_assign_types(ast.location_get(),
                           ast::AssignExpr::AssignOp::ASSIGN,
                           var_type, init_type);
    }

    ast.type_set(var_type);
}

void TypeChecker::operator()(ast::TypeDecl& ast)
{
    const Type* t = node_type(*ast.ty_get());
    Named* n = new Named(ast.name_get(), t);

    ast.built_type_set(n);
}

void TypeChecker::operator()(ast::RecordDecl& ast)
{
    if (ast.fields_get())
    {
        Record *r = new Record(ast.name_get(),
                               ast.record_type_get() ==
                               ast::RecordDecl::RecordType::STRUCT);

        for (auto f : ast.fields_get()->list_get())
        {
            ucc::ast::DefaultVisitor::operator()(*f);

            r->field_add(f->name_get(), f->built_type_get());
        }

        ast.built_type_set(r);
        ast.type_set(r);

        /* TODO: handle prev */
    }
}

void TypeChecker::operator()(ast::PtrTy& ast)
{
    const Type* inner = node_type(*ast.pointed_ty_get());
    Ptr* p = new Ptr(inner);

    if (ast.is_const())
    {
        Const* c = new Const(p);

        ast.built_type_set(c);
        ast.type_set(c);
    }
    else
    {
        ast.built_type_set(p);
        ast.type_set(p);
    }
}

void TypeChecker::operator()(ast::NamedTy& ast)
{
    if (ast.def_get())
        ast.type_set(ast.def_get()->built_type_get());
    else if (ast.name_get() == "char")
        ast.type_set(&Char::instance_get());
    else if (ast.name_get() == "unsigned char")
        ast.type_set(&UnsignedChar::instance_get());
    else if (ast.name_get() == "short")
        ast.type_set(&Short::instance_get());
    else if (ast.name_get() == "unsigned short")
        ast.type_set(&UnsignedShort::instance_get());
    else if (ast.name_get() == "int")
        ast.type_set(&Int::instance_get());
    else if (ast.name_get() == "unsigned int")
        ast.type_set(&UnsignedInt::instance_get());
    else if (ast.name_get() == "long")
        ast.type_set(&Long::instance_get());
    else if (ast.name_get() == "unsigned long")
        ast.type_set(&UnsignedLong::instance_get());
    else if (ast.name_get() == "long long")
        ast.type_set(&LongLong::instance_get());
    else if (ast.name_get() == "unsigned long long")
        ast.type_set(&UnsignedLongLong::instance_get());
    else if (ast.name_get() == "float")
        ast.type_set(&Float::instance_get());
    else if (ast.name_get() == "double")
        ast.type_set(&Double::instance_get());
    else if (ast.name_get() == "void")
        ast.type_set(&Void::instance_get());
    else
        assert(false && "Internal compiler error: Unknown name type");

    if (ast.is_const())
    {
        Const* c = new Const(ast.type_get());

        ast.type_set(c);
        ast.built_type_set(c);
    }
}

void TypeChecker::operator()(ast::RecordTy& ast)
{
    ast.type_set(ast.def_get()->type_get());
}

void TypeChecker::operator()(ast::IntExpr& e)
{
    e.type_set(&Int::instance_get());
}

void TypeChecker::operator()(ast::FloatExpr& e)
{
    e.type_set(&Float::instance_get());
}

void TypeChecker::operator()(ast::StringExpr& e)
{
    Ptr* str_type = new Ptr(&Char::instance_get());

    e.built_type_set(str_type);
    e.type_set(str_type);
}

void TypeChecker::operator()(ast::VarExpr& ast)
{
    const ast::VarDecl* d = dynamic_cast<const ast::VarDecl*> (ast.def_get());

    assert(d);

    ast.type_set(d->type_get());
}

void TypeChecker::operator()(ast::UnaryExpr& ast)
{
    const Type *t = node_type(*ast.expr_get());
    const Type *actual = &t->actual_type();

    switch (ast.op_get())
    {
        case ast::UnaryExpr::UnaryOp::BAND:
            {
                Ptr *p = new Ptr(t);

                ast.type_set(p);
                ast.built_type_set(p);
            }
            break;
        case ast::UnaryExpr::UnaryOp::DEREF:
            {
                const Ptr* p = dynamic_cast<const Ptr*> (actual);
                const Array* a = dynamic_cast<const Array*> (actual);

                if (p)
                    ast.type_set(p->pointed_type_get());
                else if (a)
                    ast.type_set(a->inner_type_get());
                else
                {
                    error("invalid type of argument of unary '*' (have '" +
                          t->to_str() + "')", ast.location_get());
                    ast.type_set(t);
                }
            }
            break;
        case ast::UnaryExpr::UnaryOp::PLUS:
        case ast::UnaryExpr::UnaryOp::MINUS:
            if (!dynamic_cast<const Number*> (actual))
                error("cannot use operator '" + ast.op_to_str() + "' on '" +
                      t->to_str() + "'", ast.location_get());
            ast.type_set(t);
            break;
        case ast::UnaryExpr::UnaryOp::TILDE:
            if (!dynamic_cast<const Integer*> (actual))
                error("cannot use operator '~' on '" + t->to_str() + "'",
                      ast.location_get());
            ast.type_set(t);
            break;
        case ast::UnaryExpr::UnaryOp::BANG:
            if (!dynamic_cast<const Ptr*> (actual) &&
                !dynamic_cast<const Number*> (actual))
                error("cannot use operator '!' on '" + t->to_str() + "'",
                      ast.location_get());
            ast.type_set(&Int::instance_get());
            break;
        case ast::UnaryExpr::UnaryOp::PRE_INCR:
        case ast::UnaryExpr::UnaryOp::PRE_DECR:
        case ast::UnaryExpr::UnaryOp::POST_INCR:
        case ast::UnaryExpr::UnaryOp::POST_DECR:
            if (dynamic_cast<const Const*> (t))
                error("cannot modify const expression",
                        ast.location_get());

            if (!dynamic_cast<const Ptr*> (actual) &&
                    !dynamic_cast<const Number*> (actual))
                error("cannot use operator '" + ast.op_to_str() + "' on '" +
                        t->to_str() + "'", ast.location_get());
            break;
    }
}
