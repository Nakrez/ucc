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

#ifndef UCC_TYPE_PTR_HH
# define UCC_TYPE_PTR_HH

# include <type/type.hh>
# include <type/builtin-type.hh>

# include <ir/ptr-type.hh>

namespace ucc
{
    namespace type
    {
        class Ptr : public Type
        {
            public:
                /// Constructor
                Ptr(const Type* pointed_type);

                /// Destructor
                virtual ~Ptr();

                virtual bool operator==(const Type& t) const override;

                /// \brief  Check compatibility of types on assignment
                /// \param  t   The type to check compatibility with
                /// \return Type compatibility level
                virtual TypeCompatibility
                compatible_on_assign(const Type& t) const override;

                /// \brief  Check compatibility of types on operation
                /// \param  t   The type to check compatibility with
                /// \param  op  The binary operator
                /// \return Type compatibility level
                virtual TypeCompatibility
                compatible_on_op(const Type& t,
                                 ast::OpExpr::Op op) const override;

                /// Return a string representing the type
                virtual std::string to_str() const override
                {
                    return pointed_type_->to_str() + "*";
                }

                /// Return the type pointed by the Ptr instance
                const Type* pointed_type_get() const
                {
                    return pointed_type_;
                }

                /// Return true if the Ptr instance is a 'void *'
                bool is_void_ptr() const
                {
                    return pointed_type_ == &Void::instance_get();
                }

                virtual int size() const override
                {
                    return 8;
                }

                virtual ir::sType to_ir_type(ir::Context& c) const override
                {
                    ir::PtrType *p;

                    p = new ir::PtrType(pointed_type_->to_ir_type(c));

                    return ir::sType(p);
                }

            private:
                const Type* pointed_type_;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_PTR_HH */
