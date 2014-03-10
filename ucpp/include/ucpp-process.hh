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

#ifndef UCPP_PROCESS_HH
# define UCPP_PROCESS_HH

# include <string>
# include <iostream>
# include <fstream>

# include <ucpp-lexer.hh>

class UcppProcess
{
    public:
        UcppProcess(const std::string& in, const std::string& out);
        ~UcppProcess();

        void init();
        void process();

    private:
        void print(const std::string& s);

    private:
        std::string input_;
        std::string output_;

        std::ostream *soutput_;

        UcppLexer lexer_;
        bool line_begin_;
};

#endif /* !UCPP_PROCESS_HH */
