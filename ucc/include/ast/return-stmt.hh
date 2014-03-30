#ifndef UCC_AST_RETURN_STMT_HH
# define UCC_AST_RETURN_STMT_HH

# include <ast/stmt.hh>
# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class ReturnStmt : public Stmt
        {
            public:
                ReturnStmt(const ucc::parse::location& loc);
                ReturnStmt(const ucc::parse::location& loc, Expr* expr);

                virtual ~ReturnStmt();

                Expr* expr_get();
                const Expr* expr_get() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* expr_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_RETURN_STMT_HH */
