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

#ifndef UCC_IR_FUNCTION_HH
# define UCC_IR_FUNCTION_HH

# include <list>

# include <ir/global-value.hh>
# include <ir/basic-block.hh>

namespace ucc
{
    namespace ir
    {
        class Function : public GlobalValue
        {
            public:
                Function(const misc::Symbol& name);
                virtual ~Function();

                typename std::list<BasicBlock*>::iterator begin()
                {
                    return blocks_.begin();
                }

                typename std::list<BasicBlock*>::iterator end()
                {
                    return blocks_.end();
                }

                typename std::list<BasicBlock*>::const_iterator cbegin() const
                {
                    return blocks_.cbegin();
                }

                typename std::list<BasicBlock*>::const_iterator cend() const
                {
                    return blocks_.cend();
                }

            protected:
                std::list<BasicBlock*> blocks_;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_FUNCTION_HH */
