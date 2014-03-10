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

#include <ucpp-process.hh>

UcppProcess::UcppProcess(const std::string& in, const std::string& out)
    : input_(in)
    , output_(out)
    , soutput_(nullptr)
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

    if (input_ == "-")
        lexer_.push_state(&std::cin);
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

        lexer_.push_state(in);
    }
}

void UcppProcess::process()
{
    while (!lexer_.eof())
        ;
}
