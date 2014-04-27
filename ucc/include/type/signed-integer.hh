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

#ifndef UCC_TYPE_SIGNED_INTEGER_HH
# define UCC_TYPE_SIGNED_INTEGER_HH

# include <type/integer.hh>

namespace ucc
{
    namespace type
    {
        class SignedInteger : public Integer
        {
            public:
                SignedInteger() = default;

                virtual ~SignedInteger() = default;

                virtual TypeCompatibility
                compatible_on_assign(const Type& t) const override;

                virtual TypeCompatibility
                compatible_on_op(const Type&, ast::OpExpr::Op) const override;

                virtual std::string to_str() const = 0;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_SIGNED_NUMBER_HH */
