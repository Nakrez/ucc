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

#ifndef UCPP_LEXER_HXX
# define UCPP_LEXER_HXX

# include <ucpp-lexer.hh>

inline void UcppLexer::out_set(std::ostream *out)
{
    out_ = out;
}

inline void UcppLexer::push_state(std::istream *stream, const std::string& f)
{
    buffers_.push(new LexerState(stream, out_, f));
}

inline void UcppLexer::pop_state()
{
    buffers_.pop();
}

inline bool UcppLexer::eof() const
{
    return buffers_.top()->eof();
}

inline void UcppLexer::preprocess_line_set(bool b)
{
    buffers_.top()->preprocess_line_set(b);
}

inline Token UcppLexer::next()
{
    return buffers_.top()->next();
}

inline unsigned UcppLexer::line_get() const
{
    return buffers_.top()->line_get();
}

inline unsigned UcppLexer::column_get() const
{
    return buffers_.top()->column_get();
}

inline const std::string& UcppLexer::file_name_get() const
{
    return buffers_.top()->file_name_get();
}

inline void UcppLexer::skip_line()
{
    return buffers_.top()->skip_line();
}

#endif /* !UCPP_LEXER_HXX */
