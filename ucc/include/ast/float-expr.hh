#ifndef UCC_AST_FLOAT_EXPR_HH
# define UCC_AST_FLOAT_EXPR_HH

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class FloatExpr : public Expr
        {
            public:
                FloatExpr(const ucc::parse::location& loc, long double val);
                virtual ~FloatExpr();

                long double value_get() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                long double val_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FLOAT_EXPR_HH */
