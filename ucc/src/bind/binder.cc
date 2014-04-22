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

#include <bind/binder.hh>
#include <ast/all.hh>

using namespace ucc;
using namespace bind;

Binder::Binder()
    : scope_()
    , record_enum_()
    , loop_switch_()
{}

Binder::~Binder()
{}

void Binder::error(const ucc::ast::Ast& ast, std::string msg)
{
    ucc::misc::Diagnostic d;

    d << ucc::misc::Diagnostic::Severity::err
      << ucc::misc::Diagnostic::Type::bind << msg << ast.location_get();

    ucc::misc::DiagnosticReporter::instance_get().add(d);
}

void Binder::operator()(ucc::ast::VarDecl& ast)
{
    if (ast.ty_get())
        ast.ty_get()->accept(*this);

    ast::Decl* d;
    ast::VarDecl* vd;

    d = scope_.get_scope(ast.name_get());

    vd = dynamic_cast<ast::VarDecl*> (d);

    if (d && !vd)
        error(ast, "Redefinition of '" + ast.name_get().data_get() +
                   "' as different kind of symbol");
    else if (vd && vd->init_get() && ast.init_get())
        error(ast, "Redefinition of " + ast.name_get().data_get());
    else if (scope_.size() > 1 && vd)
        error(ast, "Redefinition of " + ast.name_get().data_get());
    else
    {
        if (vd)
            ast.prev_set(vd);

        if (ast.name_get().data_get() != "")
            scope_.put(ast.name_get(), &ast);
    }

    if (ast.init_get())
        ast.init_get()->accept(*this);
}

void Binder::operator()(ucc::ast::FunctionDecl& ast)
{
    ast::Decl* d;
    ast::FunctionDecl* vd;

    d = scope_.get_scope(ast.name_get());

    vd = dynamic_cast<ast::FunctionDecl*> (d);

    if (d && !vd)
        error(ast, "Redefinition of '" + ast.name_get().data_get() +
                   "' as different kind of symbol");
    else if (vd && vd->compound_get() && ast.compound_get())
        error(ast, "Redefinition of " + ast.name_get().data_get());
    else
    {
        if (vd)
            ast.prev_set(vd);

        scope_.put(ast.name_get(), &ast);
    }

    if (ast.return_ty_get())
        ast.return_ty_get()->accept(*this);

    scope_begin();

    for (auto param : ast.param_get())
        param->accept(*this);

    if (ast.compound_get() && ast.compound_get()->compound_get())
        ast.compound_get()->compound_get()->accept(*this);

    scope_end();
}

void Binder::operator()(ucc::ast::TypeDecl& ast)
{
    if (ast.ty_get())
        ast.ty_get()->accept(*this);

    ast::Decl* d;

    d = scope_.get_scope(ast.name_get());

    if (d)
        error(ast, "Redefinition of '" + ast.name_get().data_get() + "'");
    else
        scope_.put(ast.name_get(), &ast);
}

void Binder::operator()(ucc::ast::RecordDecl& ast)
{
    if (ast.name_get().data_get() == "")
        return;

    if (ast.fields_get())
    {
        scope_begin();

        ast.fields_get()->accept(*this);

        scope_end();
    }

    ast::RecordDecl* rd;
    ast::Decl* d;

    d = record_enum_.get_scope(ast.name_get());

    rd = dynamic_cast<ast::RecordDecl*> (d);

    if ((d && !rd) || (rd && rd->record_type_get() != ast.record_type_get()))
        error(ast, "Redefinition of '" + ast.name_get().data_get() + "' as "
                   "different kind of symbol");
    else if (rd && rd->fields_get() && ast.fields_get())
        error(ast, "Redefinition of '" + ast.name_get().data_get() + "'");
    else
    {
        if (rd)
            ast.prev_set(rd);

        record_enum_.put(ast.name_get(), &ast);
    }
}

void Binder::operator()(ucc::ast::EnumDecl& ast)
{
    if (ast.name_get().data_get() == "")
        return;

    if (ast.body_get())
        ast.body_get()->accept(*this);

    ast::EnumDecl* ed;
    ast::Decl* d;

    d = record_enum_.get_scope(ast.name_get());

    ed = dynamic_cast<ast::EnumDecl*> (d);

    if (d && !ed)
        error(ast, "Redefinition of '" + ast.name_get().data_get() + "' as "
                   "different kind of symbol");
    else if (ed && ed->body_get() && ast.body_get())
        error(ast, "Redefinition of '" + ast.name_get().data_get() + "'");
    else
    {
        if (ed)
            ast.prev_set(ed);

        record_enum_.put(ast.name_get(), &ast);
    }
}

void Binder::operator()(ucc::ast::EnumExprDecl& ast)
{
    ast::Decl* d;

    d = scope_.get_scope(ast.name_get());

    if (d)
        error(ast, "Redefinition of '" + ast.name_get().data_get() + "'");
    else
        scope_.put(ast.name_get(), &ast);
}

void Binder::operator()(ucc::ast::NamedTy& ast)
{
    ast::Decl* d;

    ast::TypeDecl* td;

    d = scope_.get(ast.name_get());

    td = dynamic_cast<ast::TypeDecl*> (d);

    if (!td)
    {
        if (is_builtin_type(ast.name_get()))
            return;

        error(ast, "Undeclared type '" + ast.name_get().data_get() + "'");
    }
    else
        ast.def_set(td);
}

void Binder::operator()(ucc::ast::RecordTy& ast)
{
    if (ast.name_get().data_get() == "")
        return;

    ast::Decl* d;
    ast::RecordDecl* rd;

    d = record_enum_.get(ast.name_get());

    rd = dynamic_cast<ast::RecordDecl*> (d);

    if ((d && !rd) || (rd && rd->record_type_get() != ast.record_type_get()))
        error(ast, "'" + ast.name_get().data_get() + "' used "
                   " with wrong declaration type");
    else if (!rd)
        error(ast, "Undeclared record '" + ast.name_get().data_get() + "'");
    else
        ast.def_set(rd);
}

void Binder::operator()(ucc::ast::EnumTy& ast)
{
    if (ast.name_get().data_get() == "")
        return;

    ast::Decl* d;
    ast::EnumDecl* ed;

    d = record_enum_.get(ast.name_get());

    ed = dynamic_cast<ast::EnumDecl*> (d);

    if (d && !ed)
        error(ast, "'" + ast.name_get().data_get() + "' used "
                   " with wrong declaration type");
    else if (!ed)
        error(ast, "Undeclared enum '" + ast.name_get().data_get() + "'");
    else
        ast.def_set(ed);
}

void Binder::operator()(ucc::ast::VarExpr& ast)
{
    ast::Decl* d;

    d = scope_.get(ast.name_get());

    if (!d)
        error(ast, "Undeclared identifier '" + ast.name_get().data_get() +
                   "'");
    else
        ast.def_set(d);
}

void Binder::operator()(ucc::ast::EnumExpr& ast)
{
    ast::Decl* d;

    d = scope_.get(ast.name_get());

    if (!d)
        error(ast, "Undeclared identifier '" + ast.name_get().data_get() +
                   "'");
    else
        ast.def_set(d);
}

void Binder::operator()(ucc::ast::CompoundStmt& ast)
{
    scope_begin();

    if (ast.compound_get())
        ast.compound_get()->accept(*this);

    scope_end();
}

void Binder::operator()(ucc::ast::DoWhileStmt& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    loop_switch_.push_back(&ast);

    if (ast.body_get())
        ast.body_get()->accept(*this);

    loop_switch_.pop_back();
}

void Binder::operator()(ucc::ast::WhileStmt& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    loop_switch_.push_back(&ast);

    if (ast.body_get())
        ast.body_get()->accept(*this);

    loop_switch_.pop_back();
}

void Binder::operator()(ucc::ast::ForStmt& ast)
{
    if (ast.init_get())
        ast.init_get()->accept(*this);

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    if (ast.inc_get())
        ast.inc_get()->accept(*this);

    loop_switch_.push_back(&ast);

    if (ast.body_get())
        ast.body_get()->accept(*this);

    loop_switch_.pop_back();
}

void Binder::operator()(ucc::ast::SwitchStmt& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    loop_switch_.push_back(&ast);

    if (ast.body_get())
        ast.body_get()->accept(*this);

    loop_switch_.pop_back();
}

void Binder::operator()(ucc::ast::BreakStmt& ast)
{
    if (loop_switch_.size() == 0)
        error(ast, "'break' statement outside any loop or switch statement");
    else
        ast.def_set(loop_switch_.back());
}

void Binder::operator()(ucc::ast::ContinueStmt& ast)
{
    typename std::list<ast::Stmt*>::iterator it = loop_switch_.begin();
    typename std::list<ast::Stmt*>::iterator end = loop_switch_.end();

    for (; it != end; ++it)
    {
        if (!dynamic_cast<ast::SwitchStmt*> (*it))
            break;
    }

    if (it == end)
        error(ast, "'continue' statement outside any loop statement");
    else
        ast.def_set(*it);
}

bool Binder::is_builtin_type(const ucc::misc::Symbol& s)
{
    const std::string *str = &s.data_get();

    return *str == "int" || *str == "void" || *str == "char" ||
           *str == "long" || *str == "short" || *str == "double" ||
           *str == "float" || *str == "long long" || *str == "unsigned int" ||
           *str == "signed int" || *str == "unsigned char" ||
           *str == "signed char" || *str == "signed long" ||
           *str == "unsigned long" || *str == "signed short" ||
           *str == "unsigned short" || *str == "signed long long" ||
           *str == "unsigned long long" || *str == "long double";
}
