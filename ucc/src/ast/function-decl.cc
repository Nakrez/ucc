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

#include <ast/all.hh>

using namespace ucc;
using namespace ast;

FunctionDecl::FunctionDecl(const ucc::parse::location& loc,
                           const ucc::misc::Symbol& name,
                           FunctionType* type)
    : Decl(loc, name)
    , type_(type)
    , compound_(nullptr)
{}

FunctionDecl::FunctionDecl(const ucc::parse::location& loc,
                           const ucc::misc::Symbol& name,
                           FunctionType* type,
                           CompoundStmt* compound)
    : Decl(loc, name)
    , type_(type)
    , compound_(compound)
{}

FunctionDecl::~FunctionDecl()
{
    delete type_;
    delete compound_;
}

const CompoundStmt* FunctionDecl::compound_get() const
{
    return compound_;
}

CompoundStmt* FunctionDecl::compound_get()
{
    return compound_;
}

const Type* FunctionDecl::return_type_get() const
{
    return type_->return_type_get();
}

Type* FunctionDecl::return_type_get()
{
    return type_->return_type_get();
}

const std::list<VarDecl*>& FunctionDecl::param_get() const
{
    return type_->param_get();
}

std::list<VarDecl*>& FunctionDecl::param_get()
{
    return type_->param_get();
}

void FunctionDecl::return_type_set(Type* t)
{
    type_->return_type_set(t);
}

void FunctionDecl::accept(Visitor& v)
{
    v(*this);
}

void FunctionDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
