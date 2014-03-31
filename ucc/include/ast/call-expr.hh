#ifndef UCC_AST_CALL_EXPR_HH
# define UCC_AST_CALL_EXPR_HH

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class CallExpr : public Expr
        {
            public:
                CallExpr(const ucc::parse::location& loc,
                         Expr* var,
                         ExprList* param);
                virtual ~CallExpr();

                const Expr* var_get() const;
                Expr* var_get();

                const ExprList* param_get() const;
                ExprList* param_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* var_;
                ExprList* param_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_CALL_EXPR_HH */
