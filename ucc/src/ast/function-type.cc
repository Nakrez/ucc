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
#include <ast/function-type.hh>

using namespace ucc;
using namespace ast;

FunctionType::FunctionType(const ucc::misc::location& loc)
    : Type(loc)
    , return_type_(nullptr)
    , param_()
{}

FunctionType::FunctionType(const ucc::misc::location& loc,
                           const std::list<VarDecl*>& param)
    : Type(loc)
    , return_type_(nullptr)
    , param_(param)
{}

FunctionType::~FunctionType()
{
    delete return_type_;

    for (auto decl : param_)
        delete decl;
}

const Type* FunctionType::return_type_get() const
{
    return return_type_;
}

Type* FunctionType::return_type_get()
{
    return return_type_;
}

void FunctionType::return_type_set(Type* t)
{
    return_type_ = t;
}

const std::list<VarDecl*>& FunctionType::param_get() const
{
    return param_;
}

std::list<VarDecl*>& FunctionType::param_get()
{
    return param_;
}

bool FunctionType::extends_type(Type *t)
{
    if (!return_type_)
    {
        return_type_ = t;

        return true;
    }

    return return_type_->extends_type(t);
}

void FunctionType::accept(Visitor& v)
{
    v(*this);
}

void FunctionType::accept(ConstVisitor& v) const
{
    v(*this);
}
