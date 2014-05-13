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

Function::Function(const misc::Symbol& name, FunctionType* t)
    : GlobalValue(sType(t), name)
    , f_type_(t)
{}

Function::~Function()
{
    for (auto b : blocks_)
        delete b;
}

void Function::dump(std::ostream& o) const
{
    o << "function " << *f_type_->ret_type_get() << " " << name_get() << "(";

    auto abegin = a_cbegin();
    auto aend = a_cend();

    for (auto ait = a_cbegin(); ait != aend; ++ait)
    {
        if (ait != abegin)
            o << ", ";

        (*ait)->dump(o);
    }

    o << ")" << misc::iendl << "{" << misc::incendl;

    auto fbegin = f_cbegin();
    auto fend = f_cend();

    for (auto fit = f_cbegin(); fit != fend; ++fit)
    {
        if (fit != fbegin)
            o << misc::iendl
              << "; label: '" + (*fit)->name_get().data_get() + "'"
              << misc::iendl;

        (*fit)->dump(o);
    }

    o << misc::decendl << "}";
}
