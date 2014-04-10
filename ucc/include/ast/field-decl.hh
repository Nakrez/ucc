#ifndef UCC_AST_FIELD_DECL_HH
# define UCC_AST_FIELD_DECL_HH

# include <ast/decl.hh>
# include <ast/type.hh>
# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class FieldDecl : public Decl
        {
            public:
                FieldDecl(const ucc::parse::location& loc,
                          const ucc::misc::Symbol& name,
                          Type* type,
                          Expr* bit_field);
                virtual ~FieldDecl();

                const Type* type_get() const;
                Type* type_get();

                const Expr* bit_field_get() const;
                Expr* bit_field_get();

                void type_set(Type* t);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Type* type_;
                Expr* bit_field_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FIELD_DECL_HH */
