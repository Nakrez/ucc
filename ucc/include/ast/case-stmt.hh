#ifndef UCC_AST_CASE_STMT_HH
# define UCC_AST_CASE_STMT_HH

# include <ast/stmt.hh>
# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class CaseStmt : public Stmt
        {
            public:
                CaseStmt(const ucc::parse::location& loc,
                         Expr* expr,
                         Stmt* body);
                virtual ~CaseStmt();

                const Expr* expr_get() const;
                Expr* expr_get();

                const Stmt* body_get() const;
                Stmt* body_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* expr_;
                Stmt* body_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_CASE_STMT_HH */
