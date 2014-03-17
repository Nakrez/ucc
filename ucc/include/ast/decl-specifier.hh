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
                    SCS_register = 8,
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
                };

            public:
                DeclSpecifier(const ucc::parse::location& loc);
                virtual ~DeclSpecifier();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v);

            private:
                unsigned storage_class_ : 4;
                unsigned type_qualifier_ : 3;
                unsigned function_specifier_ : 1;
                unsigned type_specifier_ : 12;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DECL_SPECIFIER_HH */
