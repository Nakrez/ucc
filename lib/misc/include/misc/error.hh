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

#ifndef UCC_MISC_ERROR_HH
# define UCC_MISC_ERROR_HH

# include <string>
# include <sstream>
# include <iostream>

namespace ucc
{
    namespace misc
    {
        class Error
        {
            public:
                enum Type
                {
                    none = 0,
                    compiler = 1,
                    lex = 2,
                    parse = 3,
                };

            public:
                Error();
                Error(const Error& err);
                ~Error();

                Error& operator=(const Error& err);

                Error& operator<<(Type type);
                Error& operator<<(const std::string& msg);
                Error& operator<<(std::ostream& (*msg) (std::ostream&));

                template <class T>
                Error& operator<<(const T& t);

                void throw_on_error() const;

                std::string msg_get() const;
                Type error_code_get() const;

            private:
                Type err_code_;
                std::stringstream msg_;
        };
    } // namespace misc
} // namespace ucc

# include <misc/error.hxx>

#endif /* !UCC_MISC_ERROR_HH */
