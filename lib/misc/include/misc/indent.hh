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

#ifndef UCC_MISC_INDENT_HH
# define UCC_MISC_INDENT_HH

# include <iosfwd>

namespace ucc
{
    namespace misc
    {
        std::ostream& iendl(std::ostream& o);
        std::ostream& incindent(std::ostream& o);
        std::ostream& decindent(std::ostream& o);
        std::ostream& incendl(std::ostream& o);
        std::ostream& decendl(std::ostream& o);
    } // namespace misc
} // namespace ucc

#endif /* !UCC_MISC_INDENT_HH */
