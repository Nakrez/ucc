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

#ifndef UCC_TYPE_RECORD_HH
# define UCC_TYPE_RECORD_HH

# include <list>

# include <misc/symbol.hh>

# include <type/type.hh>
# include <type/field.hh>

namespace ucc
{
    namespace type
    {
        class Record : public Type
        {
            public:
                /// Constructor
                Record(const ucc::misc::Symbol name, bool is_struct = true)
                    : name_(name)
                    , is_struct_(is_struct)
                {}

                /// Destructor
                virtual ~Record() = default;

                /// \brief  Add a new Field to the Record.
                /// \param  f   The field you want to add to the Record.
                void field_add(const Field& f)
                {
                    fields_.push_back(f);
                }

                /// \brief  Add a new Field to the Record.
                /// \param  n   The name of the field
                /// \param  t   The type of the field
                void field_add(const ucc::misc::Symbol& n, const Type* t)
                {
                    fields_.push_back(Field(n, t));
                }

                typename std::list<Field>::const_iterator cbegin() const
                {
                    return fields_.cbegin();
                }

                typename std::list<Field>::const_iterator cend() const
                {
                    return fields_.cend();
                }

                const std::list<Field>& fields_get() const
                {
                    return fields_;
                }

                /// \brief  Get the Type of a Field named @a name.
                /// \param  name    The name of the Field you want to get the
                ///                 Type.
                /// \return The type of the Field, or @a nullptr if the Field
                ///         does not exist.
                const Type* field_type_get(const ucc::misc::Symbol name) const;

                virtual Type::TypeCompatibility
                compatible_on_assign(const Type&) const override;

                virtual TypeCompatibility
                compatible_on_op(const Type&, ast::OpExpr::Op) const override
                {
                    return Type::TypeCompatibility::error;
                }

                virtual const Type& actual_type() const override
                {
                    return *this;
                }

                virtual std::string to_str() const override
                {
                    if (is_struct_)
                        return "struct " + name_.data_get();
                    else
                        return "union " + name_.data_get();
                }

            private:
                ucc::misc::Symbol name_;
                bool is_struct_;
                std::list<Field> fields_;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_RECORD_HH */
