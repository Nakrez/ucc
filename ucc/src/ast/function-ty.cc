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
#include <ast/function-ty.hh>

using namespace ucc;
using namespace ast;

FunctionTy::FunctionTy(const ucmp::misc::location& loc)
    : Ty(loc)
    , return_ty_(nullptr)
    , param_()
{}

FunctionTy::FunctionTy(const ucmp::misc::location& loc,
                        const std::list<VarDecl*>& param)
    : Ty(loc)
    , return_ty_(nullptr)
    , param_(param)
{}

FunctionTy::~FunctionTy()
{
    delete return_ty_;

    for (auto decl : param_)
        delete decl;
}

bool FunctionTy::extends_ty(Ty *t)
{
    if (!return_ty_)
    {
        return_ty_ = t;

        return true;
    }

    return return_ty_->extends_ty(t);
}
