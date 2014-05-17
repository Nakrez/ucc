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

#include <ast/array-ty.hh>
#include <ast/expr.hh>

using namespace ucc;
using namespace ast;

ArrayTy::ArrayTy(const ucmp::misc::location& loc)
    : Ty(loc)
    , sub_ty_(nullptr)
    , size_(nullptr)
{}

ArrayTy::ArrayTy(const ucmp::misc::location& loc, Expr* expr)
    : Ty(loc)
    , sub_ty_(nullptr)
    , size_(expr)

{}

ArrayTy::~ArrayTy()
{
    delete sub_ty_;
    delete size_;
}

bool ArrayTy::extends_ty(Ty *t)
{
    if (sub_ty_ == nullptr)
    {
        sub_ty_ = t;

        return t;
    }

    return sub_ty_->extends_ty(t);
}
