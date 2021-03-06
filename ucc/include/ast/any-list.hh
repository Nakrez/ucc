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

#ifndef UCC_AST_ANY_LIST_HH
# define UCC_AST_ANY_LIST_HH

# include <list>
# include <memory>

# include <ast/visitor.hh>

namespace ucc
{
    namespace ast
    {
        template <class T>
        class AnyList : public Ast
        {
            public:
                AnyList(const ucc::misc::location& loc);
                virtual ~AnyList();

                const std::list<std::shared_ptr<T>>& list_get() const;
                std::list<std::shared_ptr<T>>& list_get();

                void push_back(std::shared_ptr<T> elem);

                void splice_front(AnyList<T>& list);
                void splice_back(AnyList<T>& list);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

                template <class U>
                AnyList<U>* convert();

            protected:
                std::list<std::shared_ptr<T>> list_;
        };
    } // namespace ast
} // namespace ucc

# include <ast/any-list.hxx>

#endif /* !UCC_AST_ANY_LIST_HH */
