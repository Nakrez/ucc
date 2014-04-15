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

#include <ast/record-type.hh>

using namespace ucc;
using namespace ast;

RecordType::RecordType(const ucc::misc::location& loc,
                       RecordDecl::RecordType type,
                       const ucc::misc::Symbol& name)
    : Type(loc)
    , name_(name)
    , type_(type)
    , def_(nullptr)
{}

RecordType::~RecordType()
{}

const ucc::misc::Symbol& RecordType::name_get() const
{
    return name_;
}

ucc::misc::Symbol& RecordType::name_get()
{
    return name_;
}

RecordDecl::RecordType RecordType::type_get() const
{
    return type_;
}

const RecordDecl* RecordType::def_get() const
{
    return def_;
}

RecordDecl* RecordType::def_get()
{
    return def_;
}

void RecordType::def_set(RecordDecl* decl)
{
    def_ = decl;
}

void RecordType::accept(Visitor& v)
{
    v(*this);
}

void RecordType::accept(ConstVisitor& v) const
{
    v(*this);
}
