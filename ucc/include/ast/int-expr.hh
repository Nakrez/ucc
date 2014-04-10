#ifndef UCC_AST_INT_EXPR_HH
# define UCC_AST_INT_EXPR_HH

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class IntExpr : public Expr
        {
            public:
                IntExpr(const ucc::parse::location& loc, int val);
                virtual ~IntExpr();

                int value_get() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                int val_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_INT_EXPR_HH */
