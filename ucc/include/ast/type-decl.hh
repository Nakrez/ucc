#ifndef UCC_AST_TYPE_DECL_HH
# define UCC_AST_TYPE_DECL_HH

# include <ast/decl.hh>

namespace ucc
{
    namespace ast
    {
        class Type;

        class TypeDecl : public Decl
        {
            public:
                TypeDecl(const ucc::parse::location& loc,
                         const ucc::misc::Symbol& name,
                         Type* type);
                virtual ~TypeDecl();

                const Type* type_get() const;
                Type* type_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Type* type_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_TYPE_DECL_HH */
