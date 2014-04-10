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

#include <ast/pretty-printer.hh>

REGISTER_COMMAND(pretty, "ast-print", "Pretty print the input file (debug "
                 "purpose)", pretty_print, "parse");

void pretty_print()
{
    ucc::ast::PrettyPrinter printer(std::cout);

    assert(ucc::ast::the_ast &&
           "Internal error: No ast retrieved by the parser");
    printer(*ucc::ast::the_ast);
    std::cout << std::endl;
}
