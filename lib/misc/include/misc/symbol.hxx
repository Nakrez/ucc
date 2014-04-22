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

#ifndef SYMBOL_HXX
# define SYMBOL_HXX

# include <misc/symbol.hh>

inline const std::string& ucc::misc::Symbol::data_get() const
{
    return *data_;
}

inline bool ucc::misc::Symbol::operator==(const ucc::misc::Symbol& s) const
{
    return data_get() == s.data_get();
}

inline bool ucc::misc::Symbol::operator!=(const ucc::misc::Symbol& s) const
{
    return data_get() != s.data_get();
}

#endif /* !SYMBOL_HXX */
