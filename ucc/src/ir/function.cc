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

#include <misc/indent.hh>
#include <ir/function.hh>

using namespace ucc;
using namespace ir;

Function::Function(const misc::Symbol& name)
    : GlobalValue(nullptr, name)
{}

Function::~Function()
{
    for (auto b : blocks_)
        delete b;
}

void Function::dump(std::ostream& o) const
{
    o << "function " << name_get() << "()" << misc::incendl;

    auto begin = cbegin();
    auto end = cend();

    for (auto it = cbegin(); it != end; ++it)
    {
        if (it != begin)
            o << "; label: '" + (*it)->name_get().data_get() + "'"
              << misc::iendl;

        (*it)->dump(o);
    }
}
