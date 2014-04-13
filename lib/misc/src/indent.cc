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
#include <iomanip>
#include <ostream>

namespace ucc
{
    namespace misc
    {
        static inline long int& indent_level_get(std::ostream& o)
        {
            static const long int indent_index = std::ios::xalloc();

            return o.iword(indent_index);
        }

        std::ostream& iendl(std::ostream& o)
        {
            o << std::endl;

            char fill = o.fill(' ');

            return o << std::setw(indent_level_get(o)) << "" << std::setfill(fill);
        }

        std::ostream& incendl(std::ostream& o)
        {
            indent_level_get(o) += 4;

            return o << iendl;
        }

        std::ostream& decendl(std::ostream& o)
        {
            indent_level_get(o) -= 4;

            return o << iendl;
        }
    } // namespace misc
} // namespace ucc
