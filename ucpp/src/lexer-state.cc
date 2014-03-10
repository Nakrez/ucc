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

#include <lexer-state.hh>

LexerState::LexerState(std::istream *input, std::ostream *out)
    : in_(input)
    , out_(out)
    , column_(1)
    , line_(1)
    , preprocess_line_(false)
{

}

LexerState::~LexerState()
{
    if (in_ != &std::cin)
    {
        std::ifstream *in = dynamic_cast<std::ifstream*>(in);

        if (in)
        {
            in->close();
            delete in;
        }
    }
}

Token LexerState::next()
{
    return Token(Token::Type::DATA, "");
}
