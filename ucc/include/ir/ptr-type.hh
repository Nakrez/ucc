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

#ifndef UCC_IR_PTR_TYPE_HH
# define UCC_IR_PTR_TYPE_HH

# include <ir/type.hh>

namespace ucc
{
    namespace ir
    {
        class Context;

        class PtrType : public Type
        {
            public:
                PtrType(sType pointed)
                    : Type(Type::PtrTy)
                    , pointed_(pointed)
                {}

                virtual ~PtrType() = default;

                sType pointed_type_get()
                {
                    return pointed_;
                }

                virtual void dump(std::ostream& o) const override
                {
                    pointed_->dump(o);
                    o << "*";
                }

            protected:
                sType pointed_;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_PTR_TYPE_HH */
