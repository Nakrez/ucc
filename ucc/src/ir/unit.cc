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

#include <ir/unit.hh>
#include <ir/function.hh>
#include <ir/global-variable.hh>

using namespace ucc;
using namespace ir;

Unit::Unit()
{}

Unit::~Unit()
{
    for (auto f : funs_)
        delete f;
}

std::ostream& Unit::dump(std::ostream& o) const
{
    for (auto v : vars_)
    {
        v->dump(o);
        o << misc::iendl;
    }

    for (auto f : funs_)
        f->dump(o);

    return o;
}
