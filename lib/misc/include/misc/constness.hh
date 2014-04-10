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

#ifndef CONSTNESS_HH
# define CONSTNESS_HH

namespace ucc
{
    namespace misc
    {
        template <typename T>
        struct const_type
        {
            typedef const T type;
        };

        template <typename T>
        struct nonconst_type
        {
            typedef T type;
        };
    } // namespace misc
} // namespace ucc

#endif /* !CONSTNESS_HH */
