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

#include <command/command.hh>

#include <parse/driver.hh>

REGISTER_COMMAND(parse, "p|parse", "Parse the input file",
                 parse_file, "");

REGISTER_BOOLEAN(parse_trace, "parse-trace", "Activate parse trace",
                 ucc::parse::parse_trace, "");

void parse_file()
{
    ucc::parse::Driver driver;

    driver.parse_file(ucc::input_file);

    driver.error_.throw_on_error();

    if (driver.ast_)
        ucc::ast::the_ast = driver.ast_;
}
