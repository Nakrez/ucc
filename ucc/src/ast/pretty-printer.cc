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

#include <ast/pretty-printer.hh>
#include <misc/indent.hh>

using namespace ucc;
using namespace ast;

PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : DefaultConstVisitor()
    , formals_(false)
    , with_bindings_(false)
    , ostr_(ostr)
{}

PrettyPrinter::~PrettyPrinter()
{}

void PrettyPrinter::activate_bindings()
{
    with_bindings_ = true;
}

void PrettyPrinter::operator()(const AstList& ast)
{
    auto it = ast.list_get().cbegin();
    auto begin = it;
    auto end = ast.list_get().cend();

    for (; it != end; ++it)
    {
        if (it != begin)
        {
            ostr_ << ucc::misc::iendl;
        }

        (*it)->accept(*this);

        if (!dynamic_cast<const Decl*> (it->get()) &&
            !dynamic_cast<const IfStmt*> (it->get()) &&
            !dynamic_cast<const SwitchStmt*> (it->get()) &&
            !dynamic_cast<const CaseStmt*> (it->get()) &&
            !dynamic_cast<const DefaultStmt*> (it->get()) &&
            !dynamic_cast<const ForStmt*> (it->get()) &&
            !dynamic_cast<const WhileStmt*> (it->get()))
            ostr_ << ";";
    }
}

void PrettyPrinter::operator()(const DeclList& ast)
{
    auto it = ast.list_get().cbegin();
    auto begin = it;
    auto end = ast.list_get().cend();

    for (; it != end; ++it)
    {
        if (it != begin)
            ostr_ << ucc::misc::iendl;
        (*it)->accept(*this);
    }
}

void PrettyPrinter::operator()(const ExprList& ast)
{
    auto it = ast.list_get().cbegin();
    auto begin = it;
    auto end = ast.list_get().cend();

    for (; it != end; ++it)
    {
        if (it != begin)
            ostr_ << ", ";
        (*it)->accept(*this);
    }
}

void PrettyPrinter::operator()(const FieldList& ast)
{
    for (auto field : ast.list_get())
    {
        field->accept(*this);

        ostr_ << ";" << ucc::misc::iendl;
    }
}

void PrettyPrinter::operator()(const EnumExprList& ast)
{
    for (auto field : ast.list_get())
    {
        field->accept(*this);

        ostr_ << "," << ucc::misc::iendl;
    }
}

void PrettyPrinter::operator()(const VarDecl& ast)
{
    if (ast.is_elipsis())
    {
        ostr_ << "...";
        return;
    }

    if (ast.is_static())
        ostr_ << "static ";
    else if (ast.is_extern())
        ostr_ << "extern ";

    if (ast.ty_get())
    {
        if (print_fun_ptr(ast.ty_get(), ast.name_get()) ||
            print_array_ty(ast.ty_get(), ast.name_get()))
            goto end;

        ast.ty_get()->accept(*this);
    }

    if (ast.name_get().data_get() != "" &&
        !dynamic_cast<const PtrTy*> (ast.ty_get()))
        ostr_ << " ";

    ostr_ << ast.name_get();

    if (ast.init_get())
    {
        ostr_ << " = ";
        ast.init_get()->accept(*this);
    }

end:

    if (!formals_)
        ostr_ << ";";

    if (with_bindings_ && ast.name_get().data_get() != "")
    {
        ostr_ << " /* " << &ast;

        if (ast.prev_get())
            ostr_ << ", prev: " << ast.prev_get();

        ostr_<< " */";
    }
}

void PrettyPrinter::operator()(const TypeDecl& ast)
{
    ostr_ << "typedef ";

    if (ast.ty_get())
    {
        if (print_fun_ptr(ast.ty_get(), ast.name_get()) ||
            print_array_ty(ast.ty_get(), ast.name_get()))
            goto end;

        ast.ty_get()->accept(*this);
    }

    ostr_ << " " << ast.name_get();

end:
    ostr_ << ";";

    if (with_bindings_)
        ostr_ << "/* " << &ast << " */";
}

void PrettyPrinter::operator()(const FunctionDecl& ast)
{
    auto it = ast.param_get().cbegin();
    auto begin = it;
    auto end = ast.param_get().cend();

    if (ast.return_ty_get())
    {
        ast.return_ty_get()->accept(*this);

        if (!dynamic_cast<const PtrTy*>(ast.return_ty_get()))
            ostr_ << " ";
    }

    ostr_ << ast.name_get();

    if (with_bindings_)
    {
        ostr_ << " /* " << &ast;

        if (ast.prev_get())
            ostr_ << ", prev " << ast.prev_get();

        ostr_ << " */ ";
    }
    ostr_ << "(";

    bool old = formals_;

    formals_ = true;

    for (; it != end; ++it)
    {
        if (it != begin)
            ostr_ << ", ";

        (*it)->accept(*this);
    }

    formals_ = old;

    ostr_ << ")";

    if (ast.compound_get())
        ast.compound_get()->accept(*this);
    else
        ostr_ << ";";
}

void PrettyPrinter::operator()(const FieldDecl& ast)
{
    if (ast.ty_get())
        ast.ty_get()->accept(*this);

    ostr_ << " " << ast.name_get();

    if (ast.bit_field_get())
    {
        ostr_ << " : ";
        ast.bit_field_get()->accept(*this);
    }
}

void PrettyPrinter::operator()(const RecordDecl& ast)
{
    if (ast.record_type_get() == RecordDecl::RecordType::STRUCT)
        ostr_ << "struct";
    else
        ostr_ << "union";

    ostr_ << " " << ast.name_get();

    if (with_bindings_)
    {
        ostr_ << " /* " << &ast;

        if (ast.prev_get())
            ostr_ << ", prev : " << ast.prev_get();

        ostr_ << " */ ";
    }

    if (ast.fields_get())
    {
        ostr_ << misc::iendl;
        ostr_ << "{";
        ostr_ << misc::incendl;

        if (ast.fields_get())
            ast.fields_get()->accept(*this);

        ostr_ << misc::decendl;
        ostr_ << "}";
    }

    ostr_ << ";";
}

void PrettyPrinter::operator()(const EnumExprDecl& ast)
{
    ostr_ << ast.name_get();

    if (with_bindings_)
        ostr_ << " /* " << &ast << " */ ";

    if (ast.value_get())
    {
        ostr_ << " = ";
        ast.value_get()->accept(*this);
    }
}

void PrettyPrinter::operator()(const EnumDecl& ast)
{
    ostr_ << "enum";

    ostr_ << " " << ast.name_get().data_get();

    if (with_bindings_)
    {
        ostr_ << " /* " << &ast;

        if (ast.prev_get())
            ostr_ << ", prev: " << ast.prev_get();

        ostr_ << " */ ";
    }

    if (ast.body_get())
    {
        ostr_ << misc::iendl;
        ostr_ << "{";
        ostr_ << misc::incendl;

        ast.body_get()->accept(*this);

        ostr_ << misc::decendl;
        ostr_ << "}";
    }

    ostr_ << ";";
}

void PrettyPrinter::operator()(const ArrayTy& ast)
{
    if (ast.sub_ty_get())
        ast.sub_ty_get()->accept(*this);

    ostr_ << "[";

    if (ast.size_get())
        ast.size_get()->accept(*this);

    ostr_ << "]";
}

void PrettyPrinter::operator()(const NamedTy& ast)
{
    if (ast.is_const())
        ostr_ << "const ";
    if (ast.is_restrict())
        ostr_ << "restrict ";

    ostr_ << ast.name_get();

    if (with_bindings_)
        ostr_ << " /* " << ast.def_get() << " */";
}

void PrettyPrinter::operator()(const PtrTy& ast)
{
    if (ast.pointed_ty_get())
        ast.pointed_ty_get()->accept(*this);

    if (!dynamic_cast<const PtrTy*>(ast.pointed_ty_get()))
        ostr_ << " ";

    ostr_ << "*";

    if (ast.is_const())
        ostr_ << "const ";
    if (ast.is_restrict())
        ostr_ << "restrict ";
}

void PrettyPrinter::operator()(const RecordTy& ast)
{
    if (ast.record_type_get() == RecordDecl::RecordType::STRUCT)
        ostr_ << "struct";
    else
        ostr_ << "union";

    if (ast.name_get().data_get() == "")
    {
        const RecordDecl* d = ast.def_get();

        ostr_ << misc::iendl;
        ostr_ << "{";
        ostr_ << misc::incendl;

        if (d->fields_get())
            d->fields_get()->accept(*this);

        ostr_ << misc::decendl;
        ostr_ << "}";
    }
    else
    {
        ostr_ << " " << ast.name_get();

        if (with_bindings_)
            ostr_ << " /* " << ast.def_get() << " */ ";
    }
}

void PrettyPrinter::operator()(const EnumTy& ast)
{
    ostr_ << "enum";

    if (ast.name_get().data_get() == "")
    {
        const EnumDecl* d = ast.def_get();

        ostr_ << misc::iendl;
        ostr_ << "{";
        ostr_ << misc::incendl;

        if (d->body_get())
            d->body_get()->accept(*this);

        ostr_ << misc::decendl;
        ostr_ << "}";
    }
    else
    {
        ostr_ << " " << ast.name_get();
        if (with_bindings_)
            ostr_ << " /* " << ast.def_get() << " */ ";
    }
}

void PrettyPrinter::operator()(const CompoundStmt& ast)
{
    ostr_ << ucc::misc::iendl;
    ostr_ << "{" << ucc::misc::incendl;

    if (ast.compound_get())
        ast.compound_get()->accept(*this);

    ostr_ << ucc::misc::decendl << "}";
}

void PrettyPrinter::operator()(const WhileStmt& ast)
{
    ostr_ << "while ";

    if (with_bindings_)
        ostr_ << "/* " << &ast << " */ ";

    ostr_ << "(";

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << ")";

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << misc::incendl;

    if (ast.body_get())
        ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << ";" << misc::decendl;
}

void PrettyPrinter::operator()(const DoWhileStmt& ast)
{
    ostr_ << "do";

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << misc::incendl;

    if (ast.body_get())
        ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << ";" << misc::decendl;
    else
        ostr_ << " ";

    ostr_ << "while ";

    if (with_bindings_)
        ostr_ << "/* " << &ast << " */ ";

    ostr_ << "(";

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << ");";
}

void PrettyPrinter::operator()(const LabelStmt& ast)
{
    ostr_ << ast.name_get() << ":" << misc::iendl;

    if (ast.stmt_get())
        ast.stmt_get()->accept(*this);
}

void PrettyPrinter::operator()(const GotoStmt& ast)
{
    ostr_ << "goto " << ast.name_get();
}

void PrettyPrinter::operator()(const BreakStmt& ast)
{
    ostr_ << "break";

    if (with_bindings_)
        ostr_ << " /* " << ast.def_get() << " */ ";
}

void PrettyPrinter::operator()(const ContinueStmt& ast)
{
    ostr_ << "continue";

    if (with_bindings_)
        ostr_ << " /* " << ast.def_get() << " */ ";
}

void PrettyPrinter::operator()(const IfStmt& ast)
{
    ostr_ << "if (";

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << ")";

    if (!dynamic_cast<const CompoundStmt*>(ast.if_body_get()))
        ostr_ << misc::incendl;

    if (ast.if_body_get())
        ast.if_body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*>(ast.if_body_get()))
        ostr_ << ";" << misc::decendl;
    else
        ostr_ << misc::iendl;

    if (ast.else_body_get())
    {
        ostr_ << "else";

        if (!dynamic_cast<const CompoundStmt*>(ast.else_body_get()))
            ostr_ << misc::incendl;

        ast.else_body_get()->accept(*this);

        if (!dynamic_cast<const CompoundStmt*>(ast.else_body_get()))
        {
            if (!dynamic_cast<const IfStmt*>(ast.else_body_get()))
                ostr_ << ";";

            ostr_ << misc::decendl;
        }
    }
}

void PrettyPrinter::operator()(const SwitchStmt& ast)
{
    ostr_ << "switch ";

    if (with_bindings_)
        ostr_ << "/* " << &ast << " */ ";

    ostr_ << "(";

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << ")";

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << misc::incendl;

    ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << misc::decendl;
}

void PrettyPrinter::operator()(const CaseStmt& ast)
{
    ostr_ << "case ";

    if (ast.expr_get())
        ast.expr_get()->accept(*this);

    ostr_ << ":";

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << misc::incendl;

    ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << ";" << misc::decendl;
}

void PrettyPrinter::operator()(const DefaultStmt& ast)
{
    ostr_ << "default:";

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << misc::incendl;

    ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << ";" << misc::decendl;
}

void PrettyPrinter::operator()(const ReturnStmt& ast)
{
    ostr_ << "return";

    if (ast.expr_get())
    {
        ostr_ << " ";
        ast.expr_get()->accept(*this);
    }
}

void PrettyPrinter::operator()(const ForStmt& ast)
{
    ostr_ << "for ";

    if (with_bindings_)
        ostr_ << "/* " << &ast << " */ ";

    ostr_ << "(";

    if (ast.init_get())
        ast.init_get()->accept(*this);

    ostr_ << "; ";

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << "; ";

    if (ast.inc_get())
        ast.inc_get()->accept(*this);

    ostr_ << ")";

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << ucc::misc::incendl;

    if (ast.body_get())
        ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << ";" << ucc::misc::decendl;
}

void PrettyPrinter::operator()(const IntExpr& ast)
{
    ostr_ << ast.value_get();
}

void PrettyPrinter::operator()(const FloatExpr& ast)
{
    ostr_ << ast.value_get();
}

void PrettyPrinter::operator()(const StringExpr& ast)
{
    ostr_ << *ast.str_get();
}

void PrettyPrinter::operator()(const VarExpr& ast)
{
    ostr_ << ast.name_get();

    if (with_bindings_)
        ostr_ << " /* " << ast.def_get() << " */";
}

void PrettyPrinter::operator()(const SubscriptExpr& ast)
{
    if (ast.var_get())
        ast.var_get()->accept(*this);

    ostr_ << "[";

    if (ast.expr_get())
        ast.expr_get()->accept(*this);

    ostr_ << "]";
}

void PrettyPrinter::operator()(const CallExpr& ast)
{
    if (ast.var_get())
        ast.var_get()->accept(*this);

    ostr_ << "(";

    if (ast.param_get())
        ast.param_get()->accept(*this);

    ostr_ << ")";
}

void PrettyPrinter::operator()(const AssignExpr& ast)
{
    if (ast.lvalue_get())
        ast.lvalue_get()->accept(*this);

    ostr_ << " ";
    ostr_ << ast.op_to_str();
    ostr_ << " ";

    if (ast.rvalue_get())
        ast.rvalue_get()->accept(*this);
}

void PrettyPrinter::operator()(const ConditionalExpr& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << " ? ";

    if (ast.true_expr_get())
        ast.true_expr_get()->accept(*this);

    ostr_ << " : ";

    if (ast.false_expr_get())
        ast.false_expr_get()->accept(*this);
}

void PrettyPrinter::operator()(const OpExpr& ast)
{
    ostr_ << "(";

    if (ast.lexpr_get())
        ast.lexpr_get()->accept(*this);

    ostr_ << " ";
    ostr_ << ast.op_to_str();
    ostr_ << " ";

    if (ast.rexpr_get())
        ast.rexpr_get()->accept(*this);

    ostr_ << ")";
}

void PrettyPrinter::operator()(const UnaryExpr& ast)
{
    if (ast.op_get() != UnaryExpr::UnaryOp::POST_INCR &&
            ast.op_get() != UnaryExpr::UnaryOp::POST_DECR)
    {
        ostr_ << ast.op_to_str();
        ast.expr_get()->accept(*this);
    }
    else
    {
        ast.expr_get()->accept(*this);
        ostr_ << ast.op_to_str();
    }
}

void PrettyPrinter::operator()(const MemberExpr& ast)
{
    ast.lexpr_get()->accept(*this);

    if (ast.is_arrow())
        ostr_ << "->";
    else
        ostr_ << ".";

    ostr_ << ast.name_get();
}

void PrettyPrinter::operator()(const EnumExpr& ast)
{
    ostr_ << ast.name_get();
}

void PrettyPrinter::operator()(const CastExpr& ast)
{
    ostr_ << "(";

    if (ast.ty_get())
        ast.ty_get()->accept(*this);

    ostr_ << ")";

    if (ast.expr_get())
        ast.expr_get()->accept(*this);
}

void PrettyPrinter::operator()(const ImplicitCastExpr& ast)
{
    if (ast.expr_get())
        ast.expr_get()->accept(*this);
}

void PrettyPrinter::operator()(const SizeofExpr& ast)
{
    ostr_ << "sizeof (";

    if (ast.ty_get())
        ast.ty_get()->accept(*this);
    else if (ast.expr_get())
        ast.expr_get()->accept(*this);

    ostr_ << ")";
}

void PrettyPrinter::operator()(const InitListExpr& ast)
{
    ostr_ << "{ ";

    if (ast.list_get())
        ast.list_get()->accept(*this);

    ostr_ << " }";
}

bool PrettyPrinter::print_fun_ptr(const Ty* ast,
                                  const ucc::misc::Symbol& sym)
{
    const PtrTy* ptr = dynamic_cast<const PtrTy*> (ast);
    const PtrTy* tmp = nullptr;
    const FunctionTy* fn = nullptr;
    int ptr_nb = 1;

    if (ptr)
    {
        while (1)
        {
            tmp = dynamic_cast<const PtrTy*> (ptr->pointed_ty_get());

            if (!tmp)
                break;

            ++ptr_nb;
            ptr = tmp;
        }

        fn = dynamic_cast<const FunctionTy*> (ptr->pointed_ty_get());

        if (!fn)
            return false;

        if (fn->return_ty_get())
            fn->return_ty_get()->accept(*this);

        if (!dynamic_cast<const PtrTy*>(fn->return_ty_get()))
            ostr_ << " ";

        ostr_ << "(";

        for (int i = 0; i < ptr_nb; ++i)
            ostr_ << "*";

        ostr_ << sym << ")(";

        bool old = formals_;
        auto it = fn->param_get().cbegin();
        auto begin = it;
        auto end = fn->param_get().cend();

        formals_ = true;

        for (; it != end; ++it)
        {
            if (it != begin)
                ostr_ << ", ";

            (*it)->accept(*this);
        }

        formals_ = old;

        ostr_ << ")";

        return true;
    }

    return false;
}

bool PrettyPrinter::print_array_ty(const Ty* ast,
                                   const ucc::misc::Symbol& sym)
{
    const ArrayTy *t = dynamic_cast<const ArrayTy*> (ast);

    if (!t)
        return false;

    if (t->sub_ty_get())
        t->sub_ty_get()->accept(*this);

    ostr_ << " " << sym << "[";

    if (t->size_get())
        t->size_get()->accept(*this);

    ostr_ << "]";

    return true;
}
