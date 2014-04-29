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

#include <ast/enum-decl.hh>
#include <ast/all.hh>

using namespace ucc;
using namespace ast;

EnumDecl::EnumDecl(const ucc::misc::location& loc,
                   const ucc::misc::Symbol& name,
                   EnumExprList* body)
    : Decl(loc, name)
    , body_(body)
    , prev_(nullptr)
{}

EnumDecl::~EnumDecl()
{
    delete body_;
}

const EnumExprList* EnumDecl::body_get() const
{
    return body_;
}

EnumExprList* EnumDecl::body_get()
{
    return body_;
}

const EnumDecl* EnumDecl::prev_get() const
{
    return prev_;
}

EnumDecl* EnumDecl::prev_get()
{
    return prev_;
}

void EnumDecl::prev_set(EnumDecl* prev)
{
    prev_ = prev;
}

void EnumDecl::accept(Visitor& v)
{
    v(*this);
}

void EnumDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
