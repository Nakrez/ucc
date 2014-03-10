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

#ifndef UCPP_LEXER_HH
# define UCPP_LEXER_HH

# include <string>
# include <stack>
# include <iostream>
# include <fstream>

# include <lexer-state.hh>

class UcppLexer
{
    public:
        UcppLexer();
        UcppLexer(std::ostream *out);
        ~UcppLexer();

        bool push_state(const std::string& file);
        void push_state(std::istream *stream);

        void pop_state();
        bool eof() const;

        void preprocess_line_set(bool b);

        void next();

    private:
        std::stack<LexerState> buffers_;

        std::ostream *out_;
};

# include <ucpp-lexer.hxx>

#endif /* !UCPP_LEXER_HH */
