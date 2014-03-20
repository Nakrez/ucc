#ifndef UCC_AST_VAR_DECL_HH
# define UCC_AST_VAR_DECL_HH

# include <ast/decl.hh>

namespace ucc
{
    namespace ast
    {
        class Expr;
        class Type;

        class VarDecl : public Decl
        {
            public:
                VarDecl(const ucc::parse::location& loc);
                VarDecl(const ucc::parse::location& loc, Type* type);
                VarDecl(const ucc::parse::location& loc, Type* type, Expr* e);
                ~VarDecl();

                const Type* type_get() const;
                Type* type_get();

                const Expr* init_get() const;
                Expr* init_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            private:
                Type* type_;
                Expr* init_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_VAR_DECL_HH */
