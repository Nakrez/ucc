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

#ifndef UCC_IR_UNIT_HH
# define UCC_IR_UNIT_HH

# include <list>

# include <ir/visitor.hh>
# include <ir/fragment.hh>

namespace ucc
{
    namespace ir
    {
        /// Contains a hole file ir
        class Unit
        {
            public:
                Unit();
                virtual ~Unit();

                typename std::list<Fragment*>::iterator begin()
                {
                    return frags_.begin();
                }

                typename std::list<Fragment*>::iterator end()
                {
                    return frags_.end();
                }

                typename std::list<Fragment*>::const_iterator cbegin() const
                {
                    return frags_.cbegin();
                }

                typename std::list<Fragment*>::const_iterator cend() const
                {
                    return frags_.cend();
                }

                std::ostream& dump(std::ostream& o);

                void add(Fragment *f)
                {
                    frags_.push_back(f);
                }

                virtual void accept(Visitor& v)
                {
                    v(*this);
                }

                virtual void accept(ConstVisitor& v) const
                {
                    v(*this);
                }
            private:
                std::list<Fragment*> frags_;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_UNIT_HH */
