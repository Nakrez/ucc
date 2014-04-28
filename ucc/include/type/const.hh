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

#ifndef UCC_TYPE_CONST_HH
# define UCC_TYPE_CONST_HH

# include <type/type.hh>

namespace ucc
{
    namespace type
    {
        /// Implements the const qualifier with a type to ease const checking
        /// in the TypeChecker.
        class Const : public Type
        {
            public:
                Const(const Type* inner_type);
                virtual ~Const();

                virtual bool operator==(const Type& t) const override;

                /// \brief  Check compatibility of Const type on assignment
                /// \param  t   The type to check compatibility with
                /// \return Type compatibility level
                virtual TypeCompatibility
                compatible_on_assign(const Type& t) const override;

                /// \brief  Check compatibility of Const type on operation
                /// \param  t   The type to check compatibility with
                /// \param  op  The binary operator
                /// \return Type compatibility level
                virtual TypeCompatibility
                compatible_on_op(const Type& t,
                                 ast::OpExpr::Op op) const override;

                /// Return the inner type because Const type is bypassed when
                /// checking types, it is only used by TypeChecker on
                /// assignation.
                virtual const Type& actual_type() const override
                {
                    return *inner_type_;
                }

                /// Return a string representing the Const type.
                virtual std::string to_str() const override
                {
                    return inner_type_->to_str() + " const";
                }

                /// Return the inner type contained by Const instance
                const Type* inner_type_get() const
                {
                    return inner_type_;
                }

            private:
                const Type* inner_type_;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_CONST_HH */
