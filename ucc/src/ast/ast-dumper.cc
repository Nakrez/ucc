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

#include <type/function.hh>
#include <ast/ast-dumper.hh>

using namespace ucc;
using namespace ast;
using namespace misc;

AstDumper::AstDumper(std::ostream& ostr)
    : ostr_(ostr)
{}

AstDumper::~AstDumper()
{}

template <>
void AstDumper::dump_list(const std::list<VarDecl*>& list)
{
    auto it = list.cbegin();
    auto begin = list.cbegin();
    auto end = list.cend();

    for (; it != end; ++it)
    {
        if (it != begin)
            ostr_ << misc::iendl;

        (*it)->accept(*this);
    }
}

void AstDumper::operator()(const AstList& ast)
{
    ostr_ << color::blue << "AstList" << color::def << misc::incendl;

    dump_list(ast);

    ostr_ << misc::decindent;
}

void AstDumper::operator()(const DeclList& ast)
{
    ostr_ << color::blue << "DeclList" << color::def << misc::incendl;

    dump_list(ast);

    ostr_ << misc::decindent;
}

void AstDumper::operator()(const ExprList& ast)
{
    ostr_ << color::blue << "ExprList" << color::def << misc::incendl;

    dump_list(ast);

    ostr_ << misc::decindent;
}

void AstDumper::operator()(const FieldList& ast)
{
    ostr_ << color::blue << "FieldList" << color::def << misc::incendl;

    dump_list(ast);

    ostr_ << misc::decindent;
}

void AstDumper::operator()(const EnumExprList& ast)
{
    ostr_ << color::blue << "EnumExprList" << color::def << misc::incendl;

    dump_list(ast);

    ostr_ << misc::decindent;
}

void AstDumper::operator()(const VarDecl& ast)
{
    ostr_ << color::blue << "VarDecl " << color::white << ast.name_get()
          << color::green << " '" << *ast.type_get() << "'" << color::def;

    if (ast.init_get())
    {
        ostr_ << misc::incendl;
        ast.init_get()->accept(*this);
        ostr_ << misc::decindent;
    }
}

void AstDumper::operator()(const TypeDecl& ast)
{
    ostr_ << color::blue << "TypeDecl " << color::white << ast.name_get()
          << color::green << " '" << *ast.ty_get()->type_get() << "'"
          << color::def;
}

void AstDumper::operator()(const FunctionDecl& ast)
{
    const type::Function* f;

    f = dynamic_cast<const type::Function*> (ast.built_type_get());

    ostr_ << color::blue << "FunctionDecl " << color::white << ast.name_get()
          << color::green << " '" << *ast.built_type_get() << "'"
          << color::def;

    if (!f->no_param() && f->size_get() > 0)
    {
        ostr_ << misc::incendl;
        dump_list(ast.param_get());
        ostr_ << misc::decindent;
    }

    if (ast.compound_get())
    {
        ostr_ << misc::incendl;
        ast.compound_get()->accept(*this);
        ostr_ << misc::decindent;
    }
}

void AstDumper::operator()(const CompoundStmt& ast)
{
    ostr_ << color::blue << "CompoundStmt" << color::def;

    if (ast.compound_get())
    {
        ostr_ << misc::incendl;
        dump_list(*ast.compound_get());
        ostr_ << misc::decindent;
    }
}

void AstDumper::operator()(const ReturnStmt& ast)
{
    ostr_ << color::blue << "ReturnStmt" << color::def;

    if (ast.expr_get())
    {
        ostr_ << misc::incendl;
        ast.expr_get()->accept(*this);
        ostr_ << misc::decindent;
    }
}

void AstDumper::operator()(const IntExpr& ast)
{
    ostr_ << color::blue << "IntExpr " << color::white << ast.value_get()
          << color::green << " '" << *ast.type_get() << "'" << color::def;
}

void AstDumper::operator()(const VarExpr& ast)
{
    ostr_ << color::blue << "VarExpr " << color::white << ast.name_get()
          << color::green << " '" << *ast.type_get() << "'" << color::def;
}

void AstDumper::operator()(const AssignExpr& ast)
{
    ostr_ << color::blue << "AssignExpr " << color::def
          << "'" << ast.op_to_str() << "'" << color::green << " '"
          << *ast.type_get() << "'" << color::def << misc::incendl;

    ast.lvalue_get()->accept(*this);

    ostr_ << misc::iendl;

    ast.rvalue_get()->accept(*this);

    ostr_ << misc::decindent;
}

void AstDumper::operator()(const CastExpr& ast)
{
    ostr_ << color::blue << "CastExpr" << color::green << " '"
          << *ast.type_get() << "'" << color::def << misc::incendl;

    ast.expr_get()->accept(*this);

    ostr_ << misc::decindent;
}
