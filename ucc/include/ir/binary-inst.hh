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

#ifndef UCC_IR_BINARY_INST_HH
# define UCC_IR_BINARY_INST_HH

# include <ir/instruction.hh>
# include <ir/use.hh>

namespace ucc
{
    namespace ir
    {
        class BinaryInst : public Instruction
        {
            public:
                enum BinOp
                {
                    ADD,
                    SUB,
                    MUL,
                    DIV,
                    MOD,
                };
            public:
                BinaryInst(BinOp op, Type* type, Use* op1, Use* op2);
                BinaryInst(BinOp op, Type* type, Use* op1, Use* op2,
                           const misc::Symbol& name);
                virtual ~BinaryInst();

                virtual void dump(std::ostream& o) const override;
            private:
                BinOp op_;
                Use* op1_;
                Use* op2_;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_BINARY_INST_HH */
