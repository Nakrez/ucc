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

#ifndef UCC_TYPE_TYPE_HH
# define UCC_TYPE_TYPE_HH

# include <ostream>

# include <ast/op-expr.hh>

namespace ucc
{
    namespace type
    {
        /// Mother class representing a type
        class Type
        {
            public:
                /// Describe type compatibility
                enum TypeCompatibility
                {
                    /// Types are compatible
                    full,

                    /// Types are not fully compatible but it is not consider
                    /// as an error. Note: TypeChecker should emit warning
                    warning,

                    /// Types are not compatible
                    error
                };

            public:
                /// Constructor
                Type()
                    : is_complete_(true)
                {}

                /// Destructor
                virtual ~Type()
                {}

                virtual bool operator==(const Type& t) const;

                bool operator!=(const Type& t) const
                {
                    return !(*this == t);
                }

                bool is_complete() const
                {
                    return is_complete_;
                }

                void set_complete(bool b)
                {
                    is_complete_ = b;
                }

                /// \brief  Check compatibility of types on assignment
                /// \param  t   The type to check compatibility with
                /// \return Type compatibility level
                virtual TypeCompatibility
                compatible_on_assign(const Type& t) const = 0;

                /// \brief  Check compatibility of types on operation
                /// \param  t   The type to check compatibility with
                /// \param  op  The binary operator
                /// \return Type compatibility level
                virtual TypeCompatibility
                compatible_on_op(const Type& t, ast::OpExpr::Op op) const = 0;

                /// Return the real type behind a node
                virtual const Type& actual_type() const
                {
                    return *this;
                }

                /// Return a string representing the type
                virtual std::string to_str() const = 0;

                /// \brief  Dump the type inside a ostream
                /// \param  o   The stream where you want to dump your type
                void dump(std::ostream& o) const
                {
                    o << to_str();
                }

            protected:
                bool is_complete_;
        };
    } // namespace type
} // namespace ucc

/// Override operator<< to accept any Type.
inline std::ostream& operator<<(std::ostream& o, const ucc::type::Type& t)
{
    t.dump(o);

    return o;
}

#endif /* !UCC_TYPE_TYPE_HH */
