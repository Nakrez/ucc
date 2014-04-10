#ifndef UCC_AST_INIT_LIST_EXPR_HH
# define UCC_AST_INIT_LIST_EXPR_HH

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class InitListExpr : public Expr
        {
            public:
                InitListExpr(const ucc::parse::location& loc,
                             ExprList* list);
                virtual ~InitListExpr();

                const ExprList* list_get() const;
                ExprList* list_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                ExprList* list_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_INIT_LIST_EXPR_HH */
