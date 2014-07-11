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

#include <type/record.hh>

using namespace ucc;
using namespace type;

const Type* Record::field_type_get(const ucmp::misc::Symbol& name) const
{
    for (auto field : fields_)
    {
        if (field.name_get() == name)
            return field.type_get();
    }

    return nullptr;
}

int Record::field_index_get(const ucmp::misc::Symbol& name) const
{
    int count = 0;

    for (auto field : fields_)
    {
        if (field.name_get() == name)
            return count;

        ++count;
    }

    return -1;
}

Type::TypeCompatibility
Record::compatible_on_assign(const Type& t) const
{
    if (&t.actual_type() != this)
        return Type::TypeCompatibility::error;

    return Type::TypeCompatibility::full;
}

ucmp::ir::sType Record::to_ir_type(ucmp::ir::Context& c) const
{
    if (c.struct_exists(name_))
        return c.struct_get(name_);

    ucmp::ir::StructType* s = new ucmp::ir::StructType(c, name_, is_struct_);

    for (auto f : fields_)
        s->add_member(f.type_get()->to_ir_type(c));

    return c.struct_get(name_);
}

int Record::size() const
{
    int size = 0;

    if (is_struct_)
    {
        for (auto f : fields_)
            size += f.type_get()->size();
    }
    else
    {
        for (auto f : fields_)
        {
            if (size < f.type_get()->size())
                size = f.type_get()->size();
        }
    }

    return size;
}
