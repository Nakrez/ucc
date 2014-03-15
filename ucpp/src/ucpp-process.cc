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

#include <ucpp.hh>
#include <ucpp-process.hh>

UcppProcess::UcppProcess(const std::string& in, const std::string& out)
    : input_(in)
    , output_(out)
    , soutput_(nullptr)
    , line_begin_(true)
{}

UcppProcess::~UcppProcess()
{
    if (soutput_ != nullptr && soutput_ != &std::cout)
    {
        std::ofstream *out = dynamic_cast<std::ofstream*>(soutput_);

        if (out)
            out->close();

        delete out;
    }
}

void UcppProcess::init()
{
    if (output_ == "-")
        soutput_ = &std::cout;
    else
    {
        std::ofstream *out = new std::ofstream;

        out->open(output_);

        if (!out->is_open())
        {
            delete out;
            std::cerr << "Error opening " << output_ << std::endl;
            /* XXX: throw */
            return;
        }

        soutput_ = out;
    }

    lexer_.out_set(soutput_);

    if (input_ == "-")
        lexer_.push_state(&std::cin, "<stdin>");
    else
    {
        std::ifstream *in = new std::ifstream;

        in->open(input_);

        if (!in->is_open())
        {
            delete in;
            std::cerr << "Error opening " << input_ << std::endl;
            /* XXX: throw */
            return;
        }

        lexer_.push_state(in, input_);
    }
}

void UcppProcess::process()
{
    Token t;

    while (1)
    {
        t = lexer_.next();

        if (t.type_get() == Token::Type::EOL)
        {
            line_begin_ = true;
            *soutput_ << std::endl;
        }
        else if (t.data_get() == "#")
            directive();
        else if (t.type_get() == Token::Type::END_OF_FILE)
                break;
        else
        {
            print(t.data_get());

            line_begin_ = false;
        }
    }
}

void UcppProcess::directive()
{
    Token t(lexer_.next());

    if (t.type_get() == Token::Type::IDENTIFIER)
    {

    }
    else if (t.type_get() == Token::Type::NUMBER)
    {

    }
    else
    {
        ucpp::error(lexer_.line_get(),
                    lexer_.column_get() - 1,
                    lexer_.file_name_get(),
                    "invalid preprocessing directive: #" + t.data_get());
    }
}

void UcppProcess::print(const std::string& p)
{
    if (line_begin_)
        *soutput_ << p;
    else
    {
        unsigned i = 0;

        for (; (p.at(i) == ' ' || p.at(i) == '\t') && i < p.size(); ++i)
            ;

        *soutput_ << " ";

        for (; i < p.size(); ++i)
            *soutput_ << p.at(i);
    }
}
