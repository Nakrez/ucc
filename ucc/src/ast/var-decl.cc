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

#include <ast/var-decl.hh>

#include <ast/expr.hh>
#include <ast/type.hh>

using namespace ucc;
using namespace ast;

VarDecl::VarDecl(const ucc::parse::location& loc,
                 const ucc::misc::Symbol& name,
                 Type* type,
                 Expr* e)
    : Decl(loc, name)
    , type_(type)
    , init_(e)
    , is_elipsis_(false)
{}

VarDecl::VarDecl(const ucc::parse::location& loc)
    : Decl(loc, "")
    , type_(nullptr)
    , init_(nullptr)
    , is_elipsis_(true)
{}

VarDecl::~VarDecl()
{
    delete type_;
    delete init_;
}

const Type* VarDecl::type_get() const
{
    return type_;
}

Type* VarDecl::type_get()
{
    return type_;
}

const Expr* VarDecl::init_get() const
{
    return init_;
}

Expr* VarDecl::init_get()
{
    return init_;
}

bool VarDecl::is_elipsis() const
{
    return is_elipsis_;
}

void VarDecl::accept(Visitor& v)
{
    v(*this);
}

void VarDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
