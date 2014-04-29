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

#include <bind/binder.hh>

REGISTER_COMMAND(bind, "b|compute-bindings", "Compute bindings on the AST",
                 bind, "parse");

void bind()
{
    ucc::bind::Binder binder;

    if (!ucc::ast::the_ast)
    {
        ucc::misc::Diagnostic d;

        d << ucc::misc::Diagnostic::Severity::critical
          << ucc::misc::Diagnostic::Type::internal
          << "No ast retrieved by the parser";

        ucc::misc::DiagnosticReporter::instance_get().add(d);
    }

    binder(*ucc::ast::the_ast);

    ucc::misc::DiagnosticReporter::instance_get().throw_on_error();
}
