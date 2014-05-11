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

#ifndef UCC_IR_INSTRUCTION_HH
# define UCC_IR_INSTRUCTION_HH

# include <ostream>
# include <ir/value.hh>

namespace ucc
{
    namespace ir
    {
        /// Base class for all IR instruction
        class Instruction : public Value
        {
            public:
                Instruction(sType t)
                    : Value(t)
                {}

                Instruction(sType t, const misc::Symbol& s)
                    : Value(t, s)
                {}

                virtual ~Instruction() = default;

                virtual void dump(std::ostream& o) const = 0;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_INSTRUCTION_HH */
