#ifndef UCC_AST_CONDITIONAL_EXPR_HH
# define UCC_AST_CONDITIONAL_EXPR_HH

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class ConditionalExpr : public Expr
        {
            public:
                ConditionalExpr(const ucc::parse::location& loc,
                                Expr* cond,
                                Expr* true_expr,
                                Expr* false_expr);
                virtual ~ConditionalExpr();

                const Expr* cond_get() const;
                Expr* cond_get();

                const Expr* true_expr_get() const;
                Expr* true_expr_get();

                const Expr* false_expr_get() const;
                Expr* false_expr_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* cond_;
                Expr* true_;
                Expr* false_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_CONDITIONAL_EXPR_HH */
