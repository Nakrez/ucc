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
#include <ir/basic-block.hh>
#include <ir/context.hh>

using namespace ucc;
using namespace ir;

BasicBlock::BasicBlock(Context& c, const misc::Symbol& s)
    : Value(c.label_ty_get(), s)
{}

BasicBlock::~BasicBlock()
{
    for (auto i : ins_)
        delete i;
}

void BasicBlock::dump(std::ostream& o) const
{
    for (auto i : ins_)
    {
        i->dump(o);
        o << misc::iendl;
    }
}
