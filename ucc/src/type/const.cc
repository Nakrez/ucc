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

#include <type/const.hh>
#include <type/builtin-type.hh>

using namespace ucc;
using namespace type;

Const::Const(Type* inner_type)
    : inner_type_(inner_type)
{}

Const::~Const()
{
    if (!dynamic_cast<Number*> (inner_type_) &&
        !dynamic_cast<Void*> (inner_type_))
        delete inner_type_;
}

Type::TypeCompatibility
Const::compatible_on_assign(const Type& t,
                            ast::AssignExpr::AssignOp op) const
{
    return inner_type_->compatible_on_assign(t, op);
}

Type::TypeCompatibility
Const::compatible_on_op(const Type& t,
                        ast::OpExpr::Op op) const
{
    return inner_type_->compatible_on_op(t, op);
}
