#ifndef UCC_AST_DECL_SPECIFIER_HH
# define UCC_AST_DECL_SPECIFIER_HH

# include <misc/symbol.hh>
# include <misc/error.hh>

# include <location.hh>

# include <ast/fwd.hh>

namespace ucc
{
    namespace ast
    {
        class Type;

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
                DeclSpecifier(const ucc::parse::location& loc);
                virtual ~DeclSpecifier();

                Type* type_get();

                bool is_typedef() const;
                bool is_const() const;
                bool is_restrict() const;
                bool is_volatile() const;

                bool is_struct_or_union() const;

                DeclSpecifier::StorageClassSpecifier storage_class_get() const;

                bool storage_class_set(const StorageClassSpecifier& spec,
                                       ucc::misc::Error& err);
                bool type_qualifier_set(const TypeQualifier& qual,
                                        ucc::misc::Error& err);
                bool function_specifier_set(const FunctionSpecifier& spec,
                                            ucc::misc::Error& err);
                bool type_specifier_set(const TypeSpecifier& spec,
                                        ucc::misc::Error& err);

                void type_name_set(const ucc::misc::Symbol& s);

                bool merge(const DeclSpecifier* decl, ucc::misc::Error& err);

                RecordDecl* record_decl_get() const;
                void record_decl_set(RecordDecl* rec);

            private:
                std::string
                storage_class_to_str(StorageClassSpecifier spec) const;

            private:
                ucc::parse::location loc_;
                StorageClassSpecifier storage_class_;
                unsigned type_qualifier_ : 3;
                FunctionSpecifier function_specifier_;
                unsigned type_specifier_ : 13;
                ucc::misc::Symbol type_name_;
                RecordDecl* rec_decl_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DECL_SPECIFIER_HH */
