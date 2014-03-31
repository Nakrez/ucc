#ifndef UCC_AST_UNARY_EXPR_HH
# define UCC_AST_UNARY_EXPR_HH

# include <string>

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class UnaryExpr : public Expr
        {
            public:
                enum UnaryOp
                {
                    BAND,
                    DEREF,
                    PLUS,
                    MINUS,
                    TILDE,
                    BANG,
                    PRE_INCR,
                    PRE_DECR,
                };

                UnaryExpr(const ucc::parse::location& loc,
                          UnaryOp op,
                          Expr* expr);
                virtual ~UnaryExpr();

                UnaryOp op_get() const;

                std::string op_to_str() const;

                const Expr* expr_get() const;
                Expr* expr_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* expr_;
                UnaryOp op_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_UNARY_EXPR_HH */
