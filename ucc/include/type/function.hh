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

#ifndef UCC_TYPE_FUNCTION_HH
# define UCC_TYPE_FUNCTION_HH

# include <type/type.hh>
# include <type/record.hh>

namespace ucc
{
    namespace type
    {
        class Function : public Type
        {
            public:
                Function(Type* return_type);

                /// Destructor
                virtual ~Function();

                /// Return the return type of the Function
                const Type* return_type_get() const
                {
                    return return_type_;
                }

                virtual TypeCompatibility
                compatible_on_assign(const Type&) const override
                {
                    // You cannot assign a function to another
                    // You cannot event declare such type
                    // So this method will be used to check function call

                    /* TODO */
                    return Type::TypeCompatibility::error;
                }

                virtual TypeCompatibility
                compatible_on_op(const Type&,
                                 ast::OpExpr::Op) const override
                {
                    return Type::TypeCompatibility::error;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    /* TODO */
                    return "";
                }

            private:
                Type* return_type_;
                Record args_;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_FUNCTION_HH */
