#ifndef UCC_AST_MEMBER_EXPR_HH
# define UCC_AST_MEMBER_EXPR_HH

# include <misc/symbol.hh>

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class MemberExpr : public Expr
        {
            public:
                MemberExpr(const ucc::parse::location& loc,
                           Expr* lexpr,
                           const ucc::misc::Symbol& name,
                           bool is_arrow);
                virtual ~MemberExpr();

                const Expr* lexpr_get() const;
                Expr* lexpr_get();

                const ucc::misc::Symbol& name_get() const;
                ucc::misc::Symbol& name_get();

                bool is_arrow() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* lexpr_;
                ucc::misc::Symbol name_;
                bool is_arrow_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_MEMBER_EXPR_HH */
