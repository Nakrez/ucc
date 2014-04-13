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

#include <iostream>
#include <command/command.hh>
#include <ucpp.hh>

int main (int argc, char *argv[])
{
    char *command[2] = { nullptr, nullptr };

    command::Command::instance().extra_args_set(command);
    command::Command::instance().description_set("ucc: Micro C Compiler");
    command::Command::instance().option_set("infile outfile");

    command::Command::instance().parse_cmd(argc, argv);

    if (command[0])
        ucpp::input_file = command[0];
    if (command[1])
        ucpp::output_file = command[1];

    command::Command::instance().enable_cmd("");
    command::Command::instance().run();

    if (ucpp::_error)
        return 1;

    return 0;
}
