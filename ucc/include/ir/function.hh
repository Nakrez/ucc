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
# include <ir/function-type.hh>

namespace ucc
{
    namespace ir
    {
        class Function : public GlobalValue
        {
            typedef typename std::list<BasicBlock*>::iterator bb_iterator;
            typedef typename std::list<BasicBlock*>::const_iterator
            bb_citerator;

            typedef typename std::list<Value*>::iterator arg_iterator;
            typedef typename std::list<Value*>::const_iterator arg_citerator;

            public:
                Function(const misc::Symbol& name, FunctionType* t);
                virtual ~Function();

                bb_iterator f_begin()           { return blocks_.begin(); }
                bb_iterator f_end()             { return blocks_.end(); }
                bb_citerator f_cbegin() const   { return blocks_.cbegin(); }
                bb_citerator f_cend() const     { return blocks_.cend(); }

                arg_iterator a_begin()          { return args_.begin(); }
                arg_iterator a_end()            { return args_.end(); }
                arg_citerator a_cbegin() const  { return args_.cbegin(); }
                arg_citerator a_cend() const    { return args_.cend(); }

                void arg_add(Value* v)
                {
                    args_.push_back(v);
                    f_type_->arg_add(v->type_get());
                }

                void dump(std::ostream& o) const;

            protected:
                FunctionType* f_type_;
                std::list<Value*> args_;
                std::list<BasicBlock*> blocks_;
        };
    } // namespace ir
} // namespace ucc

#endif /* !UCC_IR_FUNCTION_HH */
