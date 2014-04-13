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

LexerState::LexerState(std::istream *input,
                       std::ostream *out,
                       const std::string& file)
    : in_(input)
    , out_(out)
    , file_(file)
    , line_offset_(0)
    , column_(1)
    , line_(0)
    , need_newline_(true)
    , preprocess_line_(false)
    , line_beginning_(true)
    , line_buffer_()
    , buffered_data_()
    , detected_type_(Token::Type::NONE)
{

}

LexerState::~LexerState()
{
    if (!in_ || in_ != &std::cin)
    {
        std::ifstream *in = dynamic_cast<std::ifstream*>(in_);

        if (in)
        {
            in->close();
            delete in;
        }
    }
}

Token LexerState::next()
{
    buffered_data_ = "";

    if (eof())
        return Token(Token::Type::END_OF_FILE, "<<EOF>>");

    if (need_newline_)
        new_line();
    else if (line_offset_ >= line_buffer_.size())
    {
        new_line();
        return Token(Token::Type::EOL, "\n");
    }

    // Treat spaces / empty lines / comments
    if (check_blank())
        return Token(Token::Type::EOL, "\n");

    if (eof())
        return Token(Token::Type::END_OF_FILE, "<<EOF>>");

    line_beginning_ = false;

    if (!punctuators() && !identifier())
    {
        // Data
        while (line_offset_ < line_buffer_.size() &&
                line_buffer_.at(line_offset_) != ' ' &&
                line_buffer_.at(line_offset_) != '\t')
        {
            buffered_data_ += line_buffer_.at(line_offset_);
            ++column_;
            ++line_offset_;
        }

        detected_type_ = Token::Type::DATA;
    }

    last_ = Token(detected_type_, buffered_data_);

    return last_;
}

bool LexerState::check_blank()
{
    while (!eof())
    {
        if (line_offset_ >= line_buffer_.size())
        {
            new_line();

            return true;
        }

        if (line_buffer_.at(line_offset_) == ' ')
            ++column_;
        else if (line_buffer_.at(line_offset_) == '\t')
            column_ += 8;
        else
            break;

        buffered_data_ += line_buffer_.at(line_offset_);
        ++line_offset_;
    }

    if (line_beginning_)
    {
        *out_ << buffered_data_;
        buffered_data_.clear();
    }
    else
        buffered_data_.clear();

    return false;
}

bool LexerState::sharp()
{
    if (line_buffer_.at(line_offset_) == '#')
    {
        ++column_;
        ++line_offset_;
        buffered_data_ += "#";

        if (line_buffer_.at(line_offset_) == '#')
        {
            buffered_data_ += "#";
            ++column_;
            ++line_offset_;

            if (preprocess_line_)
            {
                detected_type_ = Token::Type::PUNCT;
                return true;
            }
            else
            {
                buffered_data_ = "";
                column_ -= 2;
                line_offset_ -= 2;
                return false;
            }
        }
        else
        {
            detected_type_ = Token::Type::PUNCT;
            return true;
        }
    }

    return false;
}

bool LexerState::punctuators()
{
    if (sharp())
        return true;

    if (line_buffer_.at(line_offset_) == '{' ||
            line_buffer_.at(line_offset_) == '}' ||
            line_buffer_.at(line_offset_) == '[' ||
            line_buffer_.at(line_offset_) == ']')
    {
        buffered_data_ += line_buffer_.at(line_offset_);
        ++line_offset_;
        detected_type_ = Token::Type::PUNCT;
        return true;
    }

    // TODO: Digraph

    return false;
}

bool LexerState::identifier()
{
    char c = line_buffer_.at(line_offset_);

    if ((c >= 'a' && c < ('z' + 1)) ||
        (c >= 'A' && c < ('Z' + 1)) ||
        (c == '_'))
    {
        do
        {
            buffered_data_ += c;
            ++line_offset_;

            if (line_offset_ >= line_buffer_.size())
                break;

            c = line_buffer_.at(line_offset_);
        } while ((c >= 'a' && c < ('z' + 1)) ||
                 (c >= 'A' && c < ('Z' + 1)) ||
                 (c == '_') || (c >= '0' && c < ('9' + 1)));

        detected_type_ = Token::Type::IDENTIFIER;

        return true;
    }

    return false;
}
