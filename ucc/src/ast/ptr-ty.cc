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

#include <ast/ptr-ty.hh>

using namespace ucc;
using namespace ast;

PtrTy::PtrTy(const ucmp::misc::location& loc)
    : Ty(loc)
    , pointed_ty_(nullptr)
{}

PtrTy::PtrTy(const ucmp::misc::location& loc, Ty* pointed_ty)
    : Ty(loc)
    , pointed_ty_(pointed_ty)
{}

PtrTy::~PtrTy()
{
    delete pointed_ty_;
}

bool PtrTy::extends_ty(Ty *t)
{
    if (!pointed_ty_)
    {
        pointed_ty_ = t;
        return true;
    }

    return pointed_ty_->extends_ty(t);
}
