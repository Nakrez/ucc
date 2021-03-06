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

#include <misc/diagnostic-reporter.hh>

REGISTER_COMMAND(werror, "Werror", "Treat warnings as errors", werror,
                 "");

REGISTER_COMMAND(w, "w|disable-warnings", "Disable all warnings",
                 w, "");

void werror()
{
    ucc::misc::DiagnosticReporter::instance_get().set_warning_as_error();
}

void w()
{
    ucc::misc::DiagnosticReporter::instance_get().disable_warning();
}
