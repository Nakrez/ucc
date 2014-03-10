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

#ifndef LEXER_STATE_HH
# define LEXER_STATE_HH

# include <iostream>
# include <fstream>

class LexerState
{
    public:
        LexerState(std::istream *input, std::ostream *out);
        ~LexerState();

        bool eof() const;

        unsigned line_get() const;
        unsigned column_get() const;

        void preprocess_line_set(bool b);

    private:
        std::istream *in_;
        std::ostream *out_;

        unsigned column_;
        unsigned line_;

        bool preprocess_line_;

        std::string line_buffer_;
};

# include <lexer-state.hxx>

#endif /* !LEXER_STATE_HH */
