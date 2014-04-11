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

    d = scope_.get(ast.name_get());

    vd = dynamic_cast<ast::VarDecl*> (d);

    if (d && !vd)
        error(ast, "Redefinition of " + ast.name_get().data_get());
    else if (vd && vd->init_get() && ast.init_get())
        error(ast, "Redefinition of " + ast.name_get().data_get());
    else
    {
        if (vd)
            ast.prev_set(vd);

        scope_.put(ast.name_get(), &ast);
    }
}

void Binder::operator()(ucc::ast::VarExpr& ast)
{
    check_use<ast::VarExpr, ast::VarDecl>(ast);
}

ucc::misc::Error& Binder::error_get()
{
    return error_;
}
