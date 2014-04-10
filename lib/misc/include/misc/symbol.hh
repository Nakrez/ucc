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

#ifndef UCC_MISC_SYMBOL_HH
# define UCC_MISC_SYMBOL_HH

# include <string>
# include <set>

namespace ucc
{
    namespace misc
    {
        class Symbol
        {
            public:
                Symbol(const std::string& s);
                Symbol(const char* s);
                ~Symbol();

                Symbol& operator=(const Symbol& s);

                const std::string& data_get() const;

            private:
                static std::set<std::string>& symbol_set_get();

            private:
                const std::string *data_;
        };
    } // namespace misc
} // namespace ucc

std::ostream& operator<<(std::ostream& o, const ucc::misc::Symbol& s);

# include <misc/symbol.hxx>

#endif /* !UCC_MISC_SYMBOL_HH */
