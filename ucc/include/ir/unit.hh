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
# include <ostream>

namespace ucc
{
    namespace ir
    {
        class Function;

        /// Contains a hole ir file
        class Unit
        {
            typedef typename std::list<Function*>::iterator f_iterator;
            typedef typename std::list<Function*>::const_iterator f_citerator;

            public:
                Unit();
                virtual ~Unit();

                f_iterator fun_begin()          { return funs_.begin(); }
                f_iterator fun_end()            { return funs_.end(); }
                f_citerator fun_cbegin() const  { return funs_.cbegin(); }
                f_citerator fun_cend() const    { return funs_.cend(); }

                std::ostream& dump(std::ostream& o) const;

                void add_function(Function *f)
                {
                    funs_.push_back(f);
                }

            private:
                std::list<Function*> funs_;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_UNIT_HH */
