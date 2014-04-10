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

#include <ast/decl.hh>

using namespace ucc;
using namespace ast;

Decl::Decl(const ucc::parse::location& loc,
           const ucc::misc::Symbol& name)
    : Ast(loc)
    , name_(name)
    , storage_(DeclSpecifier::StorageClassSpecifier::SCS_unspecified)
{}

Decl::~Decl()
{}

const ucc::misc::Symbol& Decl::name_get() const
{
    return name_;
}

ucc::misc::Symbol& Decl::name_get()
{
    return name_;
}

bool Decl::is_static() const
{
    return storage_ == DeclSpecifier::StorageClassSpecifier::SCS_static;
}

bool Decl::is_extern() const
{
    return storage_ == DeclSpecifier::StorageClassSpecifier::SCS_extern;
}

bool Decl::is_auto() const
{
    return storage_ == DeclSpecifier::StorageClassSpecifier::SCS_auto;
}

bool Decl::is_register() const
{
    return storage_ == DeclSpecifier::StorageClassSpecifier::SCS_register;
}

DeclSpecifier::StorageClassSpecifier Decl::storage_class_get() const
{
    return storage_;
}

void Decl::storage_class_set(DeclSpecifier::StorageClassSpecifier storage)
{
    storage_ = storage;
}
