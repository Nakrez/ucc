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

#ifndef UCC_AST_DECL_SPECIFIER_HH
# define UCC_AST_DECL_SPECIFIER_HH

# include <misc/symbol.hh>
# include <misc/diagnostic-reporter.hh>
# include <misc/location.hh>

# include <ast/fwd.hh>

namespace ucc
{
    namespace ast
    {
        class Ty;

        /// Hold all declaration specifier (not present in the final as, just
        /// an help to build it)
        class DeclSpecifier
        {
            public:
                enum StorageClassSpecifier
                {
                    SCS_unspecified = 0,
                    SCS_typedef = 1,
                    SCS_extern = 2,
                    SCS_static = 4,
                    SCS_auto = 8,
                    SCS_register = 16,
                };

                enum TypeQualifier
                {
                    TQ_unspecified = 0,
                    TQ_const = 1,
                    TQ_restrict = 2,
                    TQ_volatile = 4
                };

                enum FunctionSpecifier
                {
                    FS_unspecified = 0,
                    FS_inline = 1,
                };

                enum TypeSpecifier
                {
                    TS_unspecified = 0,
                    TS_void = 1,
                    TS_char = 2,
                    TS_short = 4,
                    TS_int = 8,
                    TS_long = 16,
                    TS_float = 32,
                    TS_double = 64,
                    TS_signed = 128,
                    TS_unsigned = 256,
                    TS_struct = 512,
                    TS_union = 1024,
                    TS_enum = 2048,
                    TS_type_name = 4096,
                    TS_long_long = 8192,
                };

            public:
                /// \brief  Constructor
                /// \param  loc The location of the DeclSpecifier
                DeclSpecifier(const ucmp::misc::location& loc);

                /// Destructor
                virtual ~DeclSpecifier() = default;


                /// Return true if the declaration specifier is a typedef
                bool is_typedef() const
                {
                    return storage_class_ & SCS_typedef;
                }

                /// Return true if the declaration specifier is const
                bool is_const() const
                {
                    return type_qualifier_ & TQ_const;
                }

                /// Return true if the declaration specifier is restrict
                bool is_restrict() const
                {
                    return type_qualifier_ & TQ_restrict;
                }

                /// Return true if the declaration specifier is a typedef
                bool is_volatile() const
                {
                    return type_qualifier_ & TQ_volatile;
                }

                /// Return true if the declaration specifier is a struct or
                /// an union
                bool is_struct_or_union() const
                {
                    return (type_specifier_ & TS_union) ||
                           (type_specifier_ & TS_struct);
                }

                /// Return true if the declaration specifier is a struct
                bool is_struct() const
                {
                    return type_specifier_ & TS_struct;
                }

                /// Return true if the declaration specifier is an union
                bool is_union() const
                {
                    return type_specifier_ & TS_union;
                }

                /// Return true if the declaration specifier is an enum
                bool is_enum() const
                {
                    return type_specifier_ & TS_enum;
                }

                /// Return the type name held by the DeclSpecifier
                ucmp::misc::Symbol& name_get()
                {
                    return type_name_;
                }

                /// Return the storage class of the DeclSpecifier
                DeclSpecifier::StorageClassSpecifier storage_class_get() const
                {
                    return storage_class_;
                }

                /// Return the Ty described by the DeclSpecifier
                Ty* ty_get();

                /// \brief  Set the storage class
                /// \param  spec    The storage class you want to set
                bool storage_class_set(const StorageClassSpecifier& spec);

                /// \brief  Set the type qualifier
                /// \param  spec    The type qualifier you want to set
                bool type_qualifier_set(const TypeQualifier& qual);

                /// \brief  Set the function specifier
                /// \param  spec    The function specifier you want to set
                bool function_specifier_set(const FunctionSpecifier& spec);

                /// \brief  Set the type specifier
                /// \param  spec    The type specifier you want to set
                bool type_specifier_set(const TypeSpecifier& spec);

                /// \brief  Set the type name
                /// \param  name    The type name you want to set
                void type_name_set(const ucmp::misc::Symbol& s);

                /// \brief  Merge two DeclSpecifier
                /// \param  decl    The DeclSpecifier you want to merge with
                ///                 the current one
                bool merge(const DeclSpecifier* decl);

                /// Get the declaration node of the DeclSpecifier
                Decl* decl_get() const;

                /// \brief  Set the declaration node of the DeclSpecifier
                /// \name   rec The declaration node you want to set
                void decl_set(Decl* rec);

            private:
                std::string
                storage_class_to_str(StorageClassSpecifier spec) const;

                std::string type_to_string() const;
            private:
                ucmp::misc::location loc_;
                StorageClassSpecifier storage_class_;
                unsigned type_qualifier_ : 3;
                FunctionSpecifier function_specifier_;
                unsigned type_specifier_ : 14;
                ucmp::misc::Symbol type_name_;
                Decl* decl_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DECL_SPECIFIER_HH */
