#ifndef UCC_AST_VAR_EXPR_HH
# define UCC_AST_VAR_EXPR_HH

# include <misc/symbol.hh>

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class VarExpr : public Expr
        {
            public:
                VarExpr(const ucc::parse::location& loc,
                        const ucc::misc::Symbol& sym);
                virtual ~VarExpr();

                const misc::Symbol& name_get() const;
                misc::Symbol& name_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                ucc::misc::Symbol name_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_VAR_EXPR_HH */
