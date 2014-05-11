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

#ifndef UCC_IR_VALUE_HH
# define UCC_IR_VALUE_HH

# include <misc/symbol.hh>

# include <ir/type.hh>

namespace ucc
{
    namespace ir
    {
        class Value
        {
            public:
                Value(sType t);
                Value(sType t, const misc::Symbol& s);
                virtual ~Value() = default;

                sType type_get() const
                {
                    return type_;
                }

                const misc::Symbol name_get() const
                {
                    return name_;
                }

                virtual void dump(std::ostream& o) const
                {
                    o << *type_ << " " << name_;
                }

            protected:
                sType type_;
                misc::Symbol name_;

            private:
                misc::Symbol fresh_name()
                {
                    static unsigned long num = 0;

                    return misc::Symbol("v" + std::to_string(num++));
                }
        };
    } // namespace ir
} // namespace ucc

inline std::ostream& operator<<(std::ostream& o, const ucc::ir::Value& v)
{
    v.dump(o);

    return o;
}

#endif /* !UCC_IR_VALUE_HH */
