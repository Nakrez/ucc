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

#include <misc/symbol.hh>

using namespace ucc;
using namespace misc;

Symbol::Symbol(const std::string& s)
    : data_(&(*(symbol_set_get().insert(s).first)))
{}

Symbol::Symbol(const char* s)
    : data_(&(*(symbol_set_get().insert(s).first)))
{}

Symbol::~Symbol()
{}

Symbol& Symbol::operator=(const Symbol& s)
{
    if (this != &s)
        data_ = s.data_;

    return *this;
}

bool Symbol::operator<(const ucc::misc::Symbol& s) const
{
    return *data_ < *(s.data_);
}

std::set<std::string>& Symbol::symbol_set_get()
{
    static std::set<std::string> set;

    return set;
}

std::ostream& operator<<(std::ostream& o, const ucc::misc::Symbol& s)
{
    o << s.data_get();

    return o;
}
