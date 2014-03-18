#ifndef UCC_AST_DECL_SPECIFIER_HH
# define UCC_AST_DECL_SPECIFIER_HH

# include <misc/symbol.hh>

# include <ast/decl.hh>

namespace ucc
{
    namespace ast
    {
        class DeclSpecifier : public Decl
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
                    TS_struct_union = 512,
                    TS_enum = 1024,
                    TS_type_name = 2048,
                    TS_long_long = 4096,
                };

            public:
                DeclSpecifier(const ucc::parse::location& loc);
                virtual ~DeclSpecifier();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

                bool storage_class_set(const StorageClassSpecifier& spec);
                bool type_qualifier_set(const TypeQualifier& qual);
                bool function_specifier_set(const FunctionSpecifier& spec);
                bool type_specifier_set(const TypeSpecifier& spec);

                bool merge(const DeclSpecifier* decl);

                StorageClassSpecifier storage_class_get() const
                {
                    return storage_class_;
                }

                TypeQualifier type_qualifier_get() const
                {
                    return static_cast<TypeQualifier> (type_qualifier_);
                }

                FunctionSpecifier function_specifier_get() const
                {
                    return function_specifier_;
                }

                TypeSpecifier type_specifier_get() const
                {
                    return static_cast<TypeSpecifier> (type_specifier_);
                }

            private:
                StorageClassSpecifier storage_class_;
                unsigned type_qualifier_ : 3;
                FunctionSpecifier function_specifier_;
                unsigned type_specifier_ : 13;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DECL_SPECIFIER_HH */
