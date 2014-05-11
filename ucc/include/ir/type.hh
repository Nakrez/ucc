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

#ifndef UCC_IR_TYPE_HH
# define UCC_IR_TYPE_HH

# include <memory>
# include <ostream>

namespace ucc
{
    namespace ir
    {
        class Type
        {
            public:
                enum IrType
                {
                    VoidTy,
                    FloatTy,
                    DoubleTy,
                    LabelTy,
                    IntTy,
                    PtrTy,
                    FunctionTy,
                    StructTy,
                    ArrayTy,
                };

            public:
                Type(IrType ty);
                virtual ~Type() = default;

                IrType type_get() const
                {
                    return ty_;
                }

                virtual void dump(std::ostream& o) const;

            protected:
                IrType ty_;
        };

        typedef std::shared_ptr<Type> sType;
    } // namespace ir
} // namespace ucc

inline std::ostream& operator<<(std::ostream& o, const ucc::ir::Type& t)
{
    t.dump(o);

    return o;
}

#endif /* !UCC_IR_TYPE_HH */
