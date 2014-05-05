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

#ifndef UCC_MISC_COLOR_HH
# define UCC_MISC_COLOR_HH

# include <string>

namespace ucc
{
    namespace misc
    {
        namespace color
        {
            const std::string def = "\033[0m";
            const std::string blue = "\033[34m";
            const std::string green = "\033[32m";
            const std::string white = "\033[37m";
            const std::string red = "\033[31m";
        } // namespace color
    } // namespace misc
} // namepsace ucc

#endif /* !UCC_MISC_COLOR_HH */
