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

#ifndef UCC_AST_ANY_LIST_HXX
# define UCC_AST_ANY_LIST_HXX

# include <ast/any-list.hh>

namespace ucc
{
    namespace ast
    {
        template <class T>
        AnyList<T>::AnyList(const ucc::misc::location& loc)
            : Ast(loc)
        {}

        template <class T>
        AnyList<T>::~AnyList()
        {}

        template <class T>
        const std::list<std::shared_ptr<T>>& AnyList<T>::list_get() const
        {
            return list_;
        }

        template <class T>
        std::list<std::shared_ptr<T>>& AnyList<T>::list_get()
        {
            return list_;
        }

        template <class T>
        void AnyList<T>::push_back(std::shared_ptr<T> elem)
        {
            list_.push_back(elem);
        }

        template <class T>
        void AnyList<T>::splice_front(AnyList<T>& list)
        {
            list_.splice(list_.begin(), list.list_get());
        }

        template <class T>
        void AnyList<T>::splice_back(AnyList<T>& list)
        {
            list_.splice(list_.end(), list.list_get());
        }

        template <class T>
        template <class U>
        AnyList<U>* AnyList<T>::convert()
        {
            AnyList<U>* list = new AnyList<U>(loc_);

            for (auto elem : list_)
                list->push_back(elem);

            return list;
        }

        template <class T>
        void AnyList<T>::accept(Visitor& v)
        {
            v(*this);
        }

        template <class T>
        void AnyList<T>::accept(ConstVisitor& v) const
        {
            v(*this);
        }
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ANY_LIST_HXX */
