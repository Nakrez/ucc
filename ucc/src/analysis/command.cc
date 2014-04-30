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

#include <analysis/uninitialized-variables.hh>

REGISTER_UNIFIER(werror, "Wextra", "Enable extra warning flags",
                 "Wuninitialized");

REGISTER_UNIFIER(wall, "Wall", "Enable warning flags about constructions that "
                 "are questionable", "Wuninitialized");

REGISTER_COMMAND(uninitialized, "Wuninitialized", "Warn if variable is used "
                 "before being initialized", wuninitialized, "type-check");

void wuninitialized()
{
    ucc::analysis::UninitializedVariables checker;

    assert(ucc::ast::the_ast &&
           "Internal error: No ast retrieved by the parser");

    checker(*ucc::ast::the_ast);

    ucc::misc::DiagnosticReporter::instance_get().throw_on_error();
}
