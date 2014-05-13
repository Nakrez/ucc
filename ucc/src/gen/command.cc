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

#include <gen/generator.hh>

REGISTER_UNIFIER(uir, "uir", "Generate uir (Intermediate representation)",
                 "ir-gen ast-delete");

REGISTER_COMMAND(gen, "ir-gen", "Generate Intermediate Representation "
                 "(internal use only)", gen_ir, "fsyntax-only");

void gen_ir()
{
    ucc::gen::Generator gen(ucc::ir::global_context);

    assert(ucc::ast::the_ast &&
           "Internal error: No ast retrieved by the parser");

    gen(*ucc::ast::the_ast);
}
