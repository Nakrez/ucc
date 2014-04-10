#ifndef UCC_AST_SIZEOF_EXPR_HH
# define UCC_AST_SIZEOF_EXPR_HH

# include <ast/expr.hh>
# include <ast/type.hh>

namespace ucc
{
    namespace ast
    {
        class SizeofExpr : public Expr
        {
            public:
                SizeofExpr(const ucc::parse::location& loc,
                           Expr* expr);
                SizeofExpr(const ucc::parse::location& loc,
                           Type* type);
                virtual ~SizeofExpr();

                const Expr* expr_get() const;
                Expr* expr_get();

                const Type* type_get() const;
                Type* type_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* expr_;
                Type* type_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_SIZEOF_EXPR_HH */
