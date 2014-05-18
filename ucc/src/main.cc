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

#include <ucmp/misc/diagnostic-reporter.hh>

#include <command/command.hh>

#include <ucc.hh>

int main(int argc, char *argv[])
{
    char *input_files[1] = { nullptr };

    command::Command::instance().description_set("ucc: Micro C compiler");
    command::Command::instance().option_set("file...");
    command::Command::instance().extra_args_set(input_files);

    command::Command::instance().parse_cmd(argc, argv);

    ucc::input_file = input_files[0];

    try
    {
        command::Command::instance().run();
    }
    catch (ucmp::misc::DiagnosticReporter::Error&)
    {
        ucmp::misc::DiagnosticReporter::instance_get().flush(std::cerr);

        return ucmp::misc::DiagnosticReporter::instance_get().error_type_get();
    }

    ucmp::misc::DiagnosticReporter::instance_get().flush(std::cerr);

    return 0;
}
