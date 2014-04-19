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

#ifndef UCC_TYPE_BUILTIN_TYPE_HH
# define UCC_TYPE_BUILTIN_TYPE_HH

# include <type/floating-point.hh>
# include <type/signed-number.hh>
# include <type/unsigned-number.hh>

namespace ucc
{
    namespace type
    {
        class Float : public FloatingPoint
        {
            Float(const Float&) = delete;
            Float& operator=(const Float&) = delete;

            public:
                virtual ~Float() = default;

                static Float& instance_get()
                {
                    static Float f;

                    return f;
                }

                virtual TypeCompatibility
                compatible_on_assign(const Type& t,
                                     ast::AssignExpr::AssignOp op) const;

                virtual TypeCompatibility
                compatible_on_op(const Type& t, ast::OpExpr::Op op) const;

                virtual const Type& actual_type() const
                {
                    return *this;
                }

                virtual std::string to_str() const
                {
                    return "float";
                }

            private:
                Float() = default;
        };

        class Double : public FloatingPoint
        {
            Double(const Double&) = delete;
            Double& operator=(const Double&) = delete;

            public:
                virtual ~Double() = default;

                static Double& instance_get()
                {
                    static Double f;

                    return f;
                }

                virtual TypeCompatibility
                compatible_on_assign(const Type& t,
                                     ast::AssignExpr::AssignOp op) const;

                virtual TypeCompatibility
                compatible_on_op(const Type& t, ast::OpExpr::Op op) const;

                virtual const Type& actual_type() const
                {
                    return *this;
                }

                virtual std::string to_str() const
                {
                    return "double";
                }

            private:
                Double() = default;
        };

        class Char : public SignedNumber
        {
            Char(const Char&) = delete;
            Char& operator=(const Char&) = delete;

            public:
                virtual ~Char() = default;

                static Char& instance_get()
                {
                    static Char f;

                    return f;
                }

                virtual TypeCompatibility
                compatible_on_assign(const Type& t,
                                     ast::AssignExpr::AssignOp op) const;

                virtual TypeCompatibility
                compatible_on_op(const Type& t, ast::OpExpr::Op op) const;

                virtual const Type& actual_type() const
                {
                    return *this;
                }

                virtual std::string to_str() const
                {
                    return "Char";
                }

            private:
                Char() = default;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_BUILTIN_TYPE_HH */
