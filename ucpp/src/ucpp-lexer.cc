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

#include <ucpp-lexer.hh>

UcppLexer::UcppLexer()
    : out_(nullptr)
{}

UcppLexer::UcppLexer(std::ostream *out)
    : out_(out)
{}

UcppLexer::~UcppLexer()
{
    while (!buffers_.empty())
    {
        delete buffers_.top();
        buffers_.pop();
    }
}

bool UcppLexer::push_state(const std::string& file)
{
    std::ifstream *stream = new std::ifstream;

    stream->open(file);

    if (!stream->is_open())
    {
        delete stream;
        return false;
    }

    buffers_.push(new LexerState(stream, out_, file));

    return true;
}
