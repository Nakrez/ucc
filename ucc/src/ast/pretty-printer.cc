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
    , ostr_(ostr)
{}

PrettyPrinter::~PrettyPrinter()
{}

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

    if (ast.type_get())
    {
        if (print_fun_ptr(ast.type_get(), ast.name_get()) ||
            print_array_ty(ast.type_get(), ast.name_get()))
        {
            if (!formals_)
                ostr_ << ";";
            return;
        }

        ast.type_get()->accept(*this);
    }

    if (ast.name_get().data_get() != "" &&
        !dynamic_cast<const PtrType*> (ast.type_get()))
        ostr_ << " ";

    ostr_ << ast.name_get();

    if (ast.init_get())
    {
        ostr_ << " = ";
        ast.init_get()->accept(*this);
    }

    if (!formals_)
        ostr_ << ";";
}

void PrettyPrinter::operator()(const TypeDecl& ast)
{
    ostr_ << "typedef ";

    if (ast.type_get())
    {
        if (print_fun_ptr(ast.type_get(), ast.name_get()) ||
            print_array_ty(ast.type_get(), ast.name_get()))
        {
            ostr_ << ";";
            return;
        }

        ast.type_get()->accept(*this);
    }

    ostr_ << " " << ast.name_get() << ";";
}

void PrettyPrinter::operator()(const FunctionDecl& ast)
{
    auto it = ast.param_get().cbegin();
    auto begin = it;
    auto end = ast.param_get().cend();

    if (ast.return_type_get())
    {
        ast.return_type_get()->accept(*this);

        if (!dynamic_cast<const PtrType*>(ast.return_type_get()))
            ostr_ << " ";
    }

    ostr_ << ast.name_get();

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
    if (ast.type_get())
        ast.type_get()->accept(*this);

    ostr_ << " " << ast.name_get();

    if (ast.bit_field_get())
    {
        ostr_ << " : ";
        ast.bit_field_get()->accept(*this);
    }
}

void PrettyPrinter::operator()(const RecordDecl& ast)
{
    if (ast.name_get().data_get() == "")
        return;

    if (ast.type_get() == RecordDecl::RecordType::STRUCT)
        ostr_ << "struct";
    else
        ostr_ << "union";

    ostr_ << " " << ast.name_get();

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

    if (ast.value_get())
    {
        ostr_ << " = ";
        ast.value_get()->accept(*this);
    }
}

void PrettyPrinter::operator()(const EnumDecl& ast)
{
    if (ast.name_get().data_get() == "")
        return;

    ostr_ << "enum";

    ostr_ << " " << ast.name_get().data_get();

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

void PrettyPrinter::operator()(const ArrayType& ast)
{
    if (ast.sub_type_get())
        ast.sub_type_get()->accept(*this);

    ostr_ << "[";

    if (ast.size_get())
        ast.size_get()->accept(*this);

    ostr_ << "]";
}

void PrettyPrinter::operator()(const NamedType& ast)
{
    if (ast.is_const())
        ostr_ << "const ";
    if (ast.is_restrict())
        ostr_ << "restrict ";

    ostr_ << ast.name_get();
}

void PrettyPrinter::operator()(const PtrType& ast)
{
    if (ast.pointed_type_get())
        ast.pointed_type_get()->accept(*this);

    if (!dynamic_cast<const PtrType*>(ast.pointed_type_get()))
        ostr_ << " ";

    ostr_ << "*";

    if (ast.is_const())
        ostr_ << "const ";
    if (ast.is_restrict())
        ostr_ << "restrict ";
}

void PrettyPrinter::operator()(const RecordType& ast)
{
    if (ast.type_get() == RecordDecl::RecordType::STRUCT)
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
        ostr_ << " " << ast.name_get();
}

void PrettyPrinter::operator()(const EnumType& ast)
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
        ostr_ << " " << ast.name_get();
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
    ostr_ << "while (";

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

    ostr_ << "while (";

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

void PrettyPrinter::operator()(const BreakStmt&)
{
    ostr_ << "break";
}

void PrettyPrinter::operator()(const ContinueStmt&)
{
    ostr_ << "continue";
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
    ostr_ << "switch (";

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
    ostr_ << "for (";

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

    if (ast.type_get())
        ast.type_get()->accept(*this);

    ostr_ << ")";

    if (ast.expr_get())
        ast.expr_get()->accept(*this);
}

void PrettyPrinter::operator()(const SizeofExpr& ast)
{
    ostr_ << "sizeof (";

    if (ast.type_get())
        ast.type_get()->accept(*this);
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

bool PrettyPrinter::print_fun_ptr(const Type* ast,
        const ucc::misc::Symbol& sym)
{
    const PtrType* ptr = dynamic_cast<const PtrType*> (ast);
    const PtrType* tmp = nullptr;
    const FunctionType* fn = nullptr;
    int ptr_nb = 1;

    if (ptr)
    {
        while (1)
        {
            tmp = dynamic_cast<const PtrType*> (ptr->pointed_type_get());

            if (!tmp)
                break;

            ++ptr_nb;
            ptr = tmp;
        }

        fn = dynamic_cast<const FunctionType*> (ptr->pointed_type_get());

        if (!fn)
            return false;

        if (fn->return_type_get())
            fn->return_type_get()->accept(*this);

        if (!dynamic_cast<const PtrType*>(fn->return_type_get()))
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

bool PrettyPrinter::print_array_ty(const Type* ast,
        const ucc::misc::Symbol& sym)
{
    const ArrayType *t = dynamic_cast<const ArrayType*> (ast);

    if (!t)
        return false;

    if (t->sub_type_get())
        t->sub_type_get()->accept(*this);

    ostr_ << " " << sym << "[";

    if (t->size_get())
        t->size_get()->accept(*this);

    ostr_ << "]";

    return true;
}
