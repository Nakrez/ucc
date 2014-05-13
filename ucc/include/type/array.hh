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

#ifndef UCC_TYPE_ARRAY_HH
# define UCC_TYPE_ARRAY_HH

# include <cassert>

# include <type/type.hh>

# include <ir/array-type.hh>

namespace ucc
{
    namespace type
    {
        class Array : public Type
        {
            public:
                /// \brief  Constructor
                /// \param  inner_type  The type pointed by the array
                Array(const Type* inner_type);

                /// Destructor
                virtual ~Array() = default;

                /// Return the inner type pointed by the array Type
                const Type* inner_type_get() const
                {
                    return inner_type_;
                }

                virtual TypeCompatibility
                compatible_on_assign(const Type&) const override;

                virtual TypeCompatibility
                compatible_on_op(const Type& t,
                                 ast::OpExpr::Op op) const override;

                virtual std::string to_str() const override
                {
                    return inner_type_->to_str() + "[]";
                }

                virtual int size() const override
                {
                    return 8;
                }

                virtual ir::sType to_ir_type(ir::Context& c) const override
                {
                    ir::ArrayType *t;

                    t = new ir::ArrayType(inner_type_->to_ir_type(c), 2);

                    assert(false);

                    return ir::sType(t);
                }

            private:
                const Type* inner_type_;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_ARRAY_HH */
