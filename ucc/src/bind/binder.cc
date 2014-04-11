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
    : error_()
    , scope_()
{}

Binder::~Binder()
{}

void Binder::error(const ucc::ast::Ast& ast, std::string msg)
{
    error_ << ucc::misc::Error::Type::bind
           << ast.location_get() << ": error: " << msg << std::endl;
}

void Binder::operator()(ucc::ast::VarDecl& ast)
{
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

    if (ast.return_type_get())
        ast.return_type_get()->accept(*this);

    scope_.scope_begin();

    for (auto param : ast.param_get())
        param->accept(*this);

    if (ast.compound_get() && ast.compound_get()->compound_get())
        ast.compound_get()->compound_get()->accept(*this);

    scope_.scope_end();
}

void Binder::operator()(ucc::ast::VarExpr& ast)
{
    ast::Decl* d;

    d = scope_.get(ast.name_get());

    if (!d)
        error(ast, "Undeclared identifier " +
                   ast.name_get().data_get());
    else
        ast.def_set(d);
}

void Binder::operator()(ucc::ast::CompoundStmt& ast)
{
    scope_.scope_begin();

    if (ast.compound_get())
        ast.compound_get()->accept(*this);

    scope_.scope_end();
}

ucc::misc::Error& Binder::error_get()
{
    return error_;
}
