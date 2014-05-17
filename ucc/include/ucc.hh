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

#ifndef UCC_HH
# define UCC_HH

# include <string>

# include <ast/all.hh>
# include <ir/unit.hh>
# include <ir/context.hh>

namespace ucc
{
    extern std::string input_file;

    namespace parse
    {
        extern bool parse_trace;
    } // namespace parse

    namespace ast
    {
        extern Ast* the_ast;
    } // namespace ast

    namespace ir
    {
        extern ucmp::ir::Context global_context;
    } // namespace ir
} // namespace ucc

#endif /* !UCC_HH */
