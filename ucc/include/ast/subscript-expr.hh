#ifndef UCC_AST_SUBSCRIPT_EXP_HH
# define UCC_AST_SUBSCRIPT_EXP_HH

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class SubscriptExpr : public Expr
        {
            public:
                SubscriptExpr(const ucc::parse::location& loc,
                              Expr* var,
                              Expr* expr);
                virtual ~SubscriptExpr();

                const Expr* var_get() const;
                Expr* var_get();

                const Expr* expr_get() const;
                Expr* expr_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* var_;
                Expr* expr_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_SUBSCRIPT_EXP_HH */
