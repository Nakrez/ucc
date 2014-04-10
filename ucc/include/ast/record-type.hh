#ifndef UCC_AST_RECORD_TYPE_HH
# define UCC_AST_RECORD_TYPE_HH

# include <misc/symbol.hh>

# include <ast/type.hh>
# include <ast/record-decl.hh>

namespace ucc
{
    namespace ast
    {
        class RecordType : public Type
        {
            public:
                RecordType(const ucc::parse::location& loc,
                           RecordDecl::RecordType type,
                           const ucc::misc::Symbol& name);
                virtual ~RecordType();

                const ucc::misc::Symbol& name_get() const;
                ucc::misc::Symbol& name_get();

                RecordDecl::RecordType type_get() const;

                const RecordDecl* def_get() const;
                RecordDecl* def_get();

                void def_set(RecordDecl* decl);

                virtual bool extends_type(Type *)
                {
                    return false;
                }

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                ucc::misc::Symbol name_;
                RecordDecl::RecordType type_;
                RecordDecl* def_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_RECORD_TYPE_HH */
