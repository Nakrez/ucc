#ifndef UCC_AST_ENUM_EXPR_DECL_HH
# define UCC_AST_ENUM_EXPR_DECL_HH

# include <ast/decl.hh>
# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class EnumExprDecl : public Decl
        {
            public:
                EnumExprDecl(const ucc::parse::location& loc,
                             const ucc::misc::Symbol& name,
                             Expr* value);
                virtual ~EnumExprDecl();

                const Expr* value_get() const;
                Expr* value_get();

                void value_set(Expr* e);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* value_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ENUM_EXPR_DECL_HH */
