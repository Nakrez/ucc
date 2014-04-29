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

RecordDecl::RecordDecl(const ucc::misc::location& loc,
                       const ucc::misc::Symbol& name,
                       RecordType type,
                       FieldList* fields)
    : Decl(loc, name)
    , type_(type)
    , fields_(fields)
    , prev_(nullptr)
{}

RecordDecl::~RecordDecl()
{
    delete fields_;
}

RecordDecl::RecordType RecordDecl::record_type_get() const
{
    return type_;
}

const FieldList* RecordDecl::fields_get() const
{
    return fields_;
}

FieldList* RecordDecl::fields_get()
{
    return fields_;
}

const RecordDecl* RecordDecl::prev_get() const
{
    return prev_;
}

RecordDecl* RecordDecl::prev_get()
{
    return prev_;
}

void RecordDecl::prev_set(RecordDecl* d)
{
    prev_ = d;
}

void RecordDecl::accept(Visitor& v)
{
    v(*this);
}

void RecordDecl::accept(ConstVisitor& v) const
{
    v(*this);
}
