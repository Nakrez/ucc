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
#include <type/function.hh>

using namespace ucc;
using namespace type;

TypeChecker::TypeChecker()
    : fun_param_(false)
    , declared_fun_(nullptr)
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

bool TypeChecker::is_scalar(const Type* t)
{
    const Type* actual = &t->actual_type();

    return dynamic_cast<const Ptr*> (actual) ||
           dynamic_cast<const Number*> (actual) ||
           dynamic_cast<const Array*> (actual);
}

void TypeChecker::check_assign_types(const ucc::misc::location& loc,
                                     const Type* t1,
                                     const Type* t2)
{
    Type::TypeCompatibility c = Type::TypeCompatibility::full;

    c = t1->actual_type().compatible_on_assign(*t2);

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

bool TypeChecker::check_op_types(const ucc::misc::location& loc,
                                 ast::OpExpr::Op op,
                                 const Type* t1, const Type* t2)
{
    Type::TypeCompatibility c;

    c = t1->actual_type().compatible_on_op(*t2, op);

    if (c != Type::TypeCompatibility::full)
    {
        ucc::misc::Diagnostic d;

        if (c == Type::TypeCompatibility::error)
            d << ucc::misc::Diagnostic::Severity::err;
        else
            d << ucc::misc::Diagnostic::Severity::warn;

        d << ucc::misc::Diagnostic::Type::type << loc;
        d << "incompatible operand to '" + op_to_str(op) + "' (have '"
          << t1->to_str() << "' and '" << t2->to_str() << "')";

        ucc::misc::DiagnosticReporter::instance_get().add(d);
    }

    return c != Type::TypeCompatibility::error;
}

void TypeChecker::operator()(ast::VarDecl& ast)
{
    if (ast.is_elipsis())
        return;

    const Type* var_type = node_type(*ast.ty_get());

    if (var_type == &Void::instance_get())
    {
        if (fun_param_)
        {
            ast.type_set(var_type);

            return;
        }
        else
            error("variable '" + ast.name_get().data_get() + "' "
                  "declared void", ast.location_get());
    }
    else if (!var_type->is_complete())
        error("variable '" + ast.name_get().data_get() + "' has incomplete "
              "type '" + var_type->to_str() + "'", ast.location_get());

    if (ast.init_get())
    {
        const Type* init_type = node_type(*ast.init_get());

        check_assign_types(ast.location_get(), var_type, init_type);
    }

    ast.type_set(var_type);
}

void TypeChecker::operator()(ast::FunctionDecl& ast)
{
    bool tmp = fun_param_;
    const Type* ret_type = node_type(*ast.return_ty_get());
    Function *f = new Function(ret_type);
    const Type* p_type;

    fun_param_ = true;

    for (auto p : ast.param_get())
    {
        if (p->is_elipsis())
            f->set_elipsis();
        else
        {
            p_type = node_type(*p);

            if (p_type == &Void::instance_get())
            {
                if (p->name_get() != "")
                    error("parameter '" + p->name_get().data_get() + "' "
                          "has incomplete type", p->location_get());
                else if (ast.param_get().size() > 1)
                    error("void must be the only parameter", p->location_get());
            }

            f->param_add(p->name_get(), node_type(*p));
        }
    }

    fun_param_ = tmp;

    ast.built_type_set(f);

    if (ast.compound_get())
    {
        declared_fun_ = &ast;
        ucc::ast::DefaultVisitor::operator()(*ast.compound_get());
        declared_fun_ = nullptr;
    }

    if (ast.prev_get() && *ast.prev_get()->built_type_get() != *f)
        error("conflicting types for '" + ast.name_get().data_get() + "'",
              ast.location_get());
}

void TypeChecker::operator()(ast::TypeDecl& ast)
{
    const Type* t = node_type(*ast.ty_get());
    Named* n = new Named(ast.name_get(), t);

    ast.built_type_set(n);
}

void TypeChecker::operator()(ast::RecordDecl& ast)
{
    if (ast.prev_get() && ast.prev_get()->fields_get())
        ast.type_set(ast.prev_get()->type_get());
    else
    {
        Record *r = new Record(ast.name_get(),
                               ast.record_type_get() ==
                               ast::RecordDecl::RecordType::STRUCT);

        if (ast.fields_get())
        {
            // If there is a forward declaration the forward declaration
            // already built an empty record type so use it
            if (ast.prev_get())
            {
                delete r;
                r = dynamic_cast<Record*>(ast.prev_get()->built_type_get());

                assert(r);
            }
            else
                ast.built_type_set(r);

            ast.type_set(r);

            for (auto f : ast.fields_get()->list_get())
            {
                ucc::ast::DefaultVisitor::operator()(*f);

                if (!f->ty_get()->type_get()->is_complete())
                    error("field '" + f->name_get().data_get() + "' "
                            "has incomplete type '" +
                            f->ty_get()->type_get()->to_str() + "'",
                            ast.location_get());

                r->field_add(f->name_get(), f->ty_get()->type_get());
            }

            // Now mark the record type as complete type
            r->set_complete(true);
        }
        else
        {
            ast.built_type_set(r);
            ast.type_set(r);
        }
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
    else if (ast.name_get() == "long double")
        ast.type_set(&LongDouble::instance_get());
    else
        assert(false && "Internal compiler error: Unknown name type");

    if (ast.is_const())
    {
        Const* c = new Const(ast.type_get());

        ast.type_set(c);
        ast.built_type_set(c);
    }
}

void TypeChecker::operator()(ast::ArrayTy& ast)
{
    const Type* t = node_type(*ast.sub_ty_get());
    Array *a = new Array(t);

    ast.built_type_set(a);
    ast.type_set(a);

    if (ast.size_get())
        ast.size_get()->accept(*this);
}

void TypeChecker::operator()(ast::FunctionTy& ast)
{
    bool tmp = fun_param_;
    const Type* ret_type = node_type(*ast.return_ty_get());
    Function *f = new Function(ret_type);

    fun_param_ = true;

    for (auto p : ast.param_get())
        f->param_add(p->name_get(), node_type(*p));

    fun_param_ = tmp;

    ast.built_type_set(f);
    ast.type_set(f);
}

void TypeChecker::operator()(ast::RecordTy& ast)
{
    ast.type_set(ast.def_get()->type_get());
}

void TypeChecker::operator()(ast::ReturnStmt& ast)
{
    const Type* t = declared_fun_->built_type_get();
    const Function *f = dynamic_cast<const Function*> (t);

    if (ast.expr_get())
    {
        ast::DefaultVisitor::operator()(*ast.expr_get());

        // TODO: Change error message from standard assignation
        check_assign_types(ast.location_get(), f->return_type_get(),
                           ast.expr_get()->type_get());
    }
    else
        check_assign_types(ast.location_get(), f->return_type_get(),
                           &Void::instance_get());
}

void TypeChecker::operator()(ast::WhileStmt& ast)
{
    ucc::ast::DefaultVisitor::operator()(ast);

    if (!is_scalar(ast.cond_get()->type_get()))
        error("used '" + ast.cond_get()->type_get()->to_str() + "' type where "
              "scalar is required", ast.location_get());
}

void TypeChecker::operator()(ast::DoWhileStmt& ast)
{
    ucc::ast::DefaultVisitor::operator()(ast);

    if (!is_scalar(ast.cond_get()->type_get()))
        error("used '" + ast.cond_get()->type_get()->to_str() + "' type where "
              "scalar is required", ast.location_get());
}

void TypeChecker::operator()(ast::IfStmt& ast)
{
    ucc::ast::DefaultVisitor::operator()(ast);

    if (!is_scalar(ast.cond_get()->type_get()))
        error("used '" + ast.cond_get()->type_get()->to_str() + "' type where "
              "scalar is required", ast.location_get());
}

void TypeChecker::operator()(ast::SwitchStmt& ast)
{
    ucc::ast::DefaultVisitor::operator()(ast);

    const Type* t = &ast.cond_get()->type_get()->actual_type();
    const Integer* i = dynamic_cast<const Integer*> (t);

    if (!i)
        error("used '" + ast.cond_get()->type_get()->to_str() + "' type as "
              "switch quantity where integer type is required",
              ast.location_get());
}

void TypeChecker::operator()(ast::ForStmt& ast)
{
    ucc::ast::DefaultVisitor::operator()(ast);

    if (!is_scalar(ast.cond_get()->type_get()))
        error("used '" + ast.cond_get()->type_get()->to_str() + "' type where "
              "scalar is required", ast.location_get());
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
    const ast::VarDecl* vd = dynamic_cast<const ast::VarDecl*> (ast.def_get());
    const ast::FunctionDecl* fd;

    fd = dynamic_cast<const ast::FunctionDecl*> (ast.def_get());

    if (vd)
        ast.type_set(vd->type_get());
    else
        ast.type_set(fd->built_type_get());
}

void TypeChecker::operator()(ast::SubscriptExpr& ast)
{
    const Type* subscript_type = node_type(*ast.expr_get());
    const Type* t = node_type(*ast.var_get());

    if (!dynamic_cast<const Integer*> (subscript_type))
        error("array subscript is no an integer", ast.location_get());

    const Ptr* p = dynamic_cast<const Ptr*> (&t->actual_type());
    const Array* a = dynamic_cast<const Array*> (&t->actual_type());

    if (p)
        ast.type_set(p->pointed_type_get());
    else if (a)
        ast.type_set(a->inner_type_get());
    else
    {
        error("subscripted value is neither array nor pointer nor vector",
              ast.location_get());

        ast.type_set(t);
    }
}

void TypeChecker::operator()(ast::CallExpr& ast)
{
    const Type* t = node_type(*ast.var_get());
    const Function* f = dynamic_cast<const Function*> (&t->actual_type());
    const Ptr* p = dynamic_cast<const Ptr*> (&t->actual_type());
    const ast::VarExpr* v = dynamic_cast<const ast::VarExpr*> (ast.var_get());

    // Support for direct call of function pointer
    if (p)
        f = dynamic_cast<const Function*> (&p->pointed_type_get()->actual_type());

    if (!f)
    {
        if (v)
            error("called object '" + v->name_get().data_get() +
                  "' is not a function", ast.location_get());
        else
            error("called object is not a function", ast.location_get());
        ast.type_set(t);

        return;
    }

    ast.type_set(f->return_type_get());

    if (f->size_get() == 0)
        return;
    else if (f->no_param())
    {
        if (ast.param_get())
        {
            if (v)
                error("too many arguments to function '" +
                      v->name_get().data_get() + "'", ast.location_get());
            else
                error("too many arguments to function", ast.location_get());
        }

        return;
    }

    if (ast.param_get() &&
        ast.param_get()->list_get().size() > f->size_get() &&
        !f->has_elipsis())
    {
        if (v)
            error("too many arguments to function '" + v->name_get().data_get()
                  + "'", ast.location_get());
        else
            error("too many arguments to function", ast.location_get());

        return;
    }

    if ((!ast.param_get() && f->size_get()) ||
        ast.param_get()->list_get().size() < f->size_get())
    {
        if (v)
            error("too few arguments to function '" +
                  v->name_get().data_get() + "'", ast.location_get());
        else
            error("too few arguments to function", ast.location_get());

        return;
    }

    auto type_it = f->cbegin();
    auto type_end = f->cend();
    auto arg_it = ast.param_get()->list_get().begin();

    const Type* p_type;
    std::list<ast::Expr*> l;

    for (; type_it != type_end; ++type_it, ++arg_it)
    {
        p_type = node_type(**arg_it);

        check_assign_types((*arg_it)->location_get(), type_it->type_get(),
                           p_type);

        // FIXME: Crap
        std::shared_ptr<ast::Expr> e(new ast::ImplicitCastExpr((*arg_it)->location_get(), *arg_it));
        e->type_set(p_type);
        arg_it->swap(e);
    }
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
                {
                    if (!p->pointed_type_get()->is_complete())
                        error("dereferencing pointer to incomplete type",
                              ast.location_get());

                    ast.type_set(p->pointed_type_get());
                }
                else if (a)
                {
                    if (!a->inner_type_get()->is_complete())
                        error("dereferencing pointer to incomplete type",
                              ast.location_get());
                    ast.type_set(a->inner_type_get());
                }
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

            ast.type_set(t);
            break;
    }
}

// NOTE: The default type in case of error is set to the lvalue, maybe find
// something better to avoid other errors
void TypeChecker::operator()(ast::MemberExpr& ast)
{
    const Type* t = node_type(*ast.lexpr_get());
    const Record* rec;

    if (ast.is_arrow())
    {
        const Ptr* ptr = dynamic_cast<const Ptr*> (&t->actual_type());

        if (!ptr)
        {
            error("invalid type argument of '->' (have '" + t->to_str() + "')",
                  ast.location_get());

            // Set a default type even if it's wrong
            ast.type_set(t);

            return;
        }

        rec = dynamic_cast<const Record*> (&ptr->pointed_type_get()->actual_type());

        if (!rec)
        {
            error("request for member '" + ast.name_get().data_get() +
                  "' in something not a structure or union",
                  ast.location_get());

            // Set a default type even if it's wrong
            ast.type_set(t);

            return;
        }
    }
    else
    {
        rec = dynamic_cast<const Record*> (&t->actual_type());

        if (!rec)
        {
            error("request for member '" + ast.name_get().data_get() +
                  "' in something not a structure or union",
                  ast.location_get());

            // Set a default type even if it's wrong
            ast.type_set(t);

            return;
        }
    }

    const Type* member_type = rec->field_type_get(ast.name_get());

    if (!member_type)
    {
        error("'" + rec->to_str() + "' has no member '" +
              ast.name_get().data_get() + "'", ast.location_get());

        // Set a default type even if it's wrong
        ast.type_set(t);

        return;
    }

    ast.type_set(member_type);
}

void TypeChecker::operator()(ast::AssignExpr& ast)
{
    const Type* lvalue = node_type(*ast.lvalue_get());
    const Type* rvalue = node_type(*ast.rvalue_get());
    const Const* clvalue = dynamic_cast<const Const*> (lvalue);

    if (clvalue)
        error("assignment of read-only lvalue", ast.location_get());
    else
    {
        if (ast.op_get() == ast::AssignExpr::AssignOp::ASSIGN)
            check_assign_types(ast.location_get(), lvalue, rvalue);
        else
            check_op_types(ast.location_get(),
                           ast::assign_op_to_op_expr(ast.op_get()),
                           lvalue, rvalue);
    }

    ast::ImplicitCastExpr* e;

    e = new ast::ImplicitCastExpr(ast.rvalue_get()->location_get(),
                                  ast.rvalue_get());

    e->type_set(lvalue);

    ast.rvalue_set(e);

    ast.type_set(lvalue);
}

void TypeChecker::operator()(ast::ConditionalExpr& ast)
{
    const Type* cond = node_type(*ast.cond_get());
    const Type* texpr = node_type(*ast.true_expr_get());
    const Type* fexpr = node_type(*ast.false_expr_get());

    if (!is_scalar(cond))
        error("used '" + ast.cond_get()->type_get()->to_str() + "' type where "
              "scalar is required", ast.location_get());

    if (texpr->compatible_on_assign(*fexpr) ==
        Type::TypeCompatibility::error)
        error("type mismatch in conditional expression", ast.location_get());

    ast.type_set(texpr);
}

void TypeChecker::operator()(ast::OpExpr& ast)
{
    const Type* lexpr = node_type(*ast.lexpr_get());
    const Type* rexpr = node_type(*ast.rexpr_get());

    if (ast.op_get() != ast::OpExpr::Op::OP_COMA)
    {
        check_op_types(ast.location_get(), ast.op_get(), lexpr, rexpr);

        ast.type_set(lexpr);
    }
    else
        ast.type_set(rexpr);
}

void TypeChecker::operator()(ast::CastExpr& ast)
{
    ucc::ast::DefaultVisitor::operator()(ast);

    const Type* t = node_type(*ast.ty_get());

    ast.type_set(t);
}

void TypeChecker::operator()(ast::SizeofExpr& ast)
{
    if (ast.expr_get())
        ucc::ast::DefaultVisitor::operator()(*ast.expr_get());
    else if (ast.ty_get())
        ucc::ast::DefaultVisitor::operator()(*ast.ty_get());

    ast.type_set(&UnsignedInt::instance_get());
}
