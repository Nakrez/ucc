#ifndef UCC_AST_RECORD_DECL_HH
# define UCC_AST_RECORD_DECL_HH

# include <ast/fwd.hh>
# include <ast/decl.hh>

namespace ucc
{
    namespace ast
    {
        class RecordDecl : public Decl
        {
            public:
                enum RecordType
                {
                    NONE,
                    STRUCT,
                    UNION,
                };

            public:
                RecordDecl(const ucc::parse::location& loc,
                           const ucc::misc::Symbol& name,
                           RecordType type,
                           FieldList* fields);
                virtual ~RecordDecl();

                RecordType type_get() const;

                const FieldList* fields_get() const;
                FieldList* fields_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                RecordType type_;
                FieldList* fields_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_RECORD_DECL_HH */
