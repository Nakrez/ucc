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

#ifndef UCC_TYPE_NAMED_HH
# define UCC_TYPE_NAMED_HH

# include <cassert>

# include <misc/symbol.hh>

# include <type/type.hh>

namespace ucc
{
    namespace type
    {
        /// Represents type aliasing
        class Named : public Type
        {
            public:
                /// Constructor
                Named(const ucc::misc::Symbol& name, const Type* alias)
                    : name_(name)
                    , alias_(alias)
                {}

                /// Destructor
                virtual ~Named()
                {}

                virtual TypeCompatibility
                compatible_on_assign(const Type&) const override
                {
                    assert(false && "Internal compiler error: should not check"
                           " compatibility of named type");

                    return Type::TypeCompatibility::error;
                }

                virtual TypeCompatibility
                compatible_on_op(const Type&, ast::OpExpr::Op) const override
                {
                    assert(false && "Internal compiler error: should not check"
                           " compatibility of named type");

                    return Type::TypeCompatibility::error;
                }

                const Type& actual_type() const override
                {
                    return alias_->actual_type();
                }

                virtual std::string to_str() const override
                {
                    return name_.data_get() + " (aka " +
                           alias_->actual_type().to_str() + ")";
                }

            private:
                ucc::misc::Symbol name_;
                const Type* alias_;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_NAMED_HH */
