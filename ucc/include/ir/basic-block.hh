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

#ifndef UCC_IR_BASIC_BLOCK_HH
# define UCC_IR_BASIC_BLOCK_HH

# include <list>
# include <ostream>

# include <ir/value.hh>
# include <ir/instruction.hh>

namespace ucc
{
    namespace ir
    {
        class Context;

        /// Represent a basic block
        class BasicBlock : public Value
        {
            public:
                BasicBlock(Context& c, const misc::Symbol& s = "");
                virtual ~BasicBlock();

                typename std::list<Instruction*>::iterator begin()
                {
                    return ins_.begin();
                }

                typename std::list<Instruction*>::iterator end()
                {
                    return ins_.end();
                }

                typename std::list<Instruction*>::const_iterator cbegin() const
                {
                    return ins_.cbegin();
                }

                typename std::list<Instruction*>::const_iterator cend() const
                {
                    return ins_.cend();
                }

                void dump(std::ostream& o) const;

            protected:
                std::list<Instruction*> ins_;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_BASIC_BLOCK_HH */
