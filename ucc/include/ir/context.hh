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
# include <map>
# include <cassert>

# include <ir/type.hh>
# include <ir/struct-type.hh>

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

                void register_struct(const misc::Symbol& s, sStructType t)
                {
                    structs_[s] = t;
                }

                sStructType struct_get(const misc::Symbol& s)
                {
                    auto it = structs_.find(s);

                    assert(it != structs_.end());

                    return it->second;
                }

                sType void_ty_get()     { return void_; }
                sType float_ty_get()    { return float_; }
                sType double_ty_get()   { return double_; }
                sType label_ty_get()    { return label_; }

                sType i8_ty_get()       { return i8_; }
                sType i16_ty_get()      { return i16_; }
                sType i32_ty_get()      { return i32_; }
                sType i64_ty_get()      { return i64_; }

            protected:
                sType void_;
                sType float_;
                sType double_;
                sType label_;

                sType i8_;
                sType i16_;
                sType i32_;
                sType i64_;

                std::list<Unit*> units_;
                std::map<misc::Symbol, sStructType> structs_;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_CONTEXT_HH */
