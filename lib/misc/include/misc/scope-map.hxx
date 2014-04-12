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

#ifndef UCC_MISC_SCOPE_MAP_HXX
# define UCC_MISC_SCOPE_MAP_HXX

# include <misc/scope-map.hh>

namespace ucc
{
    namespace misc
    {
        template <class Key, class Data>
        ScopeMap<Key, Data>::ScopeMap()
            : map_()
        {
            scope_begin();
        }

        template <class Key, class Data>
        ScopeMap<Key, Data>::~ScopeMap()
        {}

        template <class Key, class Data>
        int ScopeMap<Key, Data>::size() const
        {
            return map_.size();
        }

        template <class Key, class Data>
        void ScopeMap<Key, Data>::scope_begin()
        {
            map_.push_back(std::map<Key, Data>());
        }

        template <class Key, class Data>
        void ScopeMap<Key, Data>::scope_end()
        {
            map_.pop_back();
        }

        template <class Key, class Data>
        Data ScopeMap<Key, Data>::get(const Key& key) const
        {
            typename std::map<Key, Data>::const_iterator it;
            auto lit = map_.crbegin();

            for (; lit != map_.crend(); ++lit)
            {
                it = (*lit).find(key);

                if (it == (*lit).cend())
                    continue;
                else
                    return it->second;
            }

            return (Data) 0;
        }

        template <class Key, class Data>
        Data ScopeMap<Key, Data>::get_scope(const Key& key) const
        {
            typename std::map<Key, Data>::const_iterator it;

            it = map_.back().find(key);

            if (it == map_.back().cend())
                return (Data) 0;
            else
                return it->second;
        }

        template <class Key, class Data>
        void ScopeMap<Key, Data>::put(const Key& key, Data data)
        {
            if (map_.size() == 0)
                return;

            map_.back()[key] = data;
        }
    } // namespace misc
} // namespace ucc

#endif /* !UCC_MISC_SCOPE_MAP_HXX */
