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

#include <ucc.hh>

#include <parse/driver.hh>
#include <ast/all.hh>

using namespace ucc;
using namespace parse;

Driver::Driver()
    : in_attribute_(false)
    , ast_(nullptr)
    , trace_parser_(ucc::parse::parse_trace)
    , trace_lexer_(false)
    , file_("")
{}

Driver::~Driver()
{}

void Driver::parse_file(const std::string& name)
{
    file_ = name;

    lexer_begin();

    Parser parser(*this);
    parser.set_debug_level(trace_parser_);
    parser.parse();

    lexer_end();
}

const ucmp::misc::Symbol& Driver::file_get() const
{
    return file_;
}
