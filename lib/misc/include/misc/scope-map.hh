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

#ifndef UCC_MISC_SCOPE_MAP_HH
# define UCC_MISC_SCOPE_MAP_HH

# include <list>
# include <map>

namespace ucc
{
    namespace misc
    {
        template <class Key, class Data>
        class ScopeMap
        {
            public:
                ScopeMap();
                ~ScopeMap();

                int size() const;

                void scope_begin();
                void scope_end();

                Data* get(const Key& key) const;
                void put(const Key& key, Data* data);

            private:
                std::list<std::map<Key, Data*>> map_;
        };
    } // namespace misc
} // namespace ucc

# include <misc/scope-map.hxx>

#endif /* !UCC_MISC_SCOPE_MAP_HH */
