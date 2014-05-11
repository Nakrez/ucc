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

#ifndef UCC_IR_CONTEXT_HH
# define UCC_IR_CONTEXT_HH

# include <list>

# include <ir/type.hh>
# include <ir/int-type.hh>
# include <ir/ptr-type.hh>

namespace ucc
{
    namespace ir
    {
        class Unit;

        class Context
        {
            public:
                Context();
                virtual ~Context();

                void add_unit(Unit* u)
                {
                    units_.push_back(u);
                }

                void register_ptr(PtrType* p)
                {
                    ptrs_.push_back(p);
                }

                Type* void_ty_get()     { return &void_; }
                Type* float_ty_get()    { return &float_; }
                Type* double_ty_get()   { return &double_; }
                Type* label_ty_get()    { return &label_; }

                IntType* i8_ty_get()    { return &i8_; }
                IntType* i16_ty_get()   { return &i16_; }
                IntType* i32_ty_get()   { return &i32_; }
                IntType* i64_ty_get()   { return &i64_; }

            protected:
                Type void_;
                Type float_;
                Type double_;
                Type label_;

                IntType i8_;
                IntType i16_;
                IntType i32_;
                IntType i64_;

                std::list<PtrType*> ptrs_;
                std::list<Unit*> units_;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_CONTEXT_HH */
