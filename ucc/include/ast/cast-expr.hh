#ifndef UCC_AST_CAST_EXPR_HH
# define UCC_AST_CAST_EXPR_HH

# include <ast/type.hh>
# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class CastExpr : public Expr
        {
            public:
                CastExpr(const ucc::parse::location& loc,
                         Type* type,
                         Expr* expr);
                virtual ~CastExpr();

                const Type* type_get() const;
                Type* type_get();

                const Expr* expr_get() const;
                Expr* expr_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Type* type_;
                Expr* expr_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_CAST_EXPR_HH */
