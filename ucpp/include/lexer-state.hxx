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

#ifndef LEXER_STATE_HXX
# define LEXER_STATE_HXX

# include <lexer-state.hh>

inline bool LexerState::eof() const
{
    if (!in_)
        return true;

    return in_->eof();
}

inline unsigned LexerState::line_get() const
{
    return line_;
}

inline unsigned LexerState::column_get() const
{
    return column_;
}

inline const std::string& LexerState::file_name_get() const
{
    return file_;
}

inline void LexerState::preprocess_line_set(bool b)
{
    preprocess_line_ = b;
}

inline void LexerState::skip_line()
{
    need_newline_ = true;
}

inline void LexerState::new_line()
{
    line_buffer_.clear();
    column_ = 1;
    line_offset_ = 0;
    ++line_;
    need_newline_ = false;
    std::getline(*in_, line_buffer_);
}

inline char LexerState::next_char()
{
    if (line_offset_ >= line_buffer_.size())
        return '\n';

    return line_buffer_.at(line_offset_ + 1);
}

#endif /* !LEXER_STATE_HXX */
