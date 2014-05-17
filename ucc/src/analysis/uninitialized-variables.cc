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

#include <analysis/uninitialized-variables.hh>
#include <type/array.hh>
#include <type/record.hh>

using namespace ucc;
using namespace analysis;

UninitializedVariables::UninitializedVariables()
    : in_function_(false)
{}

UninitializedVariables::~UninitializedVariables()
{}

void UninitializedVariables::warn(const std::string& msg,
                                  const ucmp::misc::location& loc)
{
    ucmp::misc::Diagnostic d;

    d << ucmp::misc::Diagnostic::Severity::warn;
    d << ucmp::misc::Diagnostic::Type::analysis << loc;
    d << msg;

    ucmp::misc::DiagnosticReporter::instance_get().add(d);
}

void UninitializedVariables::operator()(ast::FunctionDecl& ast)
{
    if (ast.return_ty_get())
        ast.return_ty_get()->accept(*this);

    for (auto param : ast.param_get())
        param->accept(*this);

    if (ast.compound_get())
    {
        in_function_ = true;
        ast.compound_get()->accept(*this);
        in_function_ = false;
    }
}

void UninitializedVariables::operator()(ast::VarDecl& ast)
{
    ast::DefaultVisitor::operator()(ast);

    if (ast.init_get())
        ast.set_initialized();
    else
    {
        const type::Array* a;

        a = dynamic_cast<const type::Array*> (ast.type_get());

        if (a)
        {
            ast.set_initialized();
            return;
        }

        const type::Record* r;

        r = dynamic_cast<const type::Record*> (ast.type_get());

        if (r)
            ast.set_initialized();
        // If the variable is global we don't emit warning, so we consider it
        // as initialized
        else if (!in_function_)
            ast.set_initialized();
    }
}

void UninitializedVariables::operator()(ast::VarExpr& ast)
{
    ast::VarDecl* v = dynamic_cast<ast::VarDecl*> (ast.def_get());

    if (!v)
        return;

    if (!v->is_initialized())
        warn("'" + ast.name_get().data_get() + "' is used uninitialized",
             ast.location_get());
}

void UninitializedVariables::operator()(ast::AssignExpr& ast)
{
    ast::VarExpr* ve = dynamic_cast<ast::VarExpr*> (ast.lvalue_get());

    ast::DefaultVisitor::operator()(*ast.rvalue_get());

    if (ve)
    {
        ast::VarDecl* vd = dynamic_cast<ast::VarDecl*> (ve->def_get());

        if (vd)
            vd->set_initialized();
    }
    else
        ast::DefaultVisitor::operator()(*ast.lvalue_get());
}
