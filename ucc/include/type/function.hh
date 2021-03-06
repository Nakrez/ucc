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
# include <type/builtin-type.hh>

namespace ucc
{
    namespace type
    {
        class Function : public Type
        {
            public:
                Function(const Type* return_type);

                /// Destructor
                virtual ~Function();

                virtual bool operator==(const Type& t) const override;

                /// Return the return type of the Function
                const Type* return_type_get() const
                {
                    return return_type_;
                }

                /// \brief  Add a parameter to the function
                /// \param  n   The name of the parameter
                /// \param  t   The type of the paramerer
                void param_add(const ucc::misc::Symbol& n, const Type* t)
                {
                    args_.field_add(n, t);
                }

                /// Return a constant iterator of the beginning of the
                /// parameter list
                typename std::list<Field>::const_iterator cbegin() const
                {
                    return args_.cbegin();
                }

                /// Return a constant iterator of the end of the
                /// parameter list
                typename std::list<Field>::const_iterator cend() const
                {
                    return args_.cend();
                }

                /// Return the number of parameter
                unsigned long size_get() const
                {
                    return args_.fields_get().size();
                }

                /// Return true if the type of the parameter is void
                /// ie : no parameter expected
                bool no_param() const
                {
                    return args_.fields_get().size() == 1 &&
                           dynamic_cast<const Void*>(args_.cbegin()->type_get()) &&
                           args_.cbegin()->name_get() == "";

                }

                /// Return true if the function contains variadic parameters
                bool has_elipsis() const
                {
                    return has_elipsis_;
                }

                /// Set if the function contains an elipsis parameter
                void set_elipsis(bool b = true)
                {
                    has_elipsis_ = b;
                }

                virtual TypeCompatibility
                compatible_on_assign(const Type&) const override
                {
                    // You cannot assign a function to another
                    // You cannot event declare such type
                    return Type::TypeCompatibility::error;
                }

                virtual TypeCompatibility
                compatible_on_op(const Type&,
                                 ast::OpExpr::Op) const override
                {
                    return Type::TypeCompatibility::error;
                }

                virtual std::string to_str() const override
                {
                    std::string args = return_type_->to_str() + "(";
                    auto begin = args_.cbegin();
                    auto it = args_.cbegin();
                    auto end = args_.cend();

                    for (; it != end; ++it)
                    {
                        if (it != begin)
                            args += ", ";

                        args += (*it).type_get()->to_str();
                    }

                    if (has_elipsis())
                    {
                        if (args_.size_get() > 0)
                            args += ", ";
                        args += "...";
                    }
                    return args + ")";
                }

            private:
                const Type* return_type_;
                Record args_;
                bool has_elipsis_;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_FUNCTION_HH */
