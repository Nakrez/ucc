#ifndef UCC_AST_IF_STMT_HH
# define UCC_AST_IF_STMT_HH

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class IfStmt : public Stmt
        {
            public:
                IfStmt(const ucc::parse::location& loc,
                       Expr* cond,
                       Stmt* if_body,
                       Stmt* else_body);
                virtual ~IfStmt();

                const Expr* cond_get() const;
                Expr* cond_get();

                const Stmt* if_body_get() const;
                Stmt* if_body_get();

                const Stmt* else_body_get() const;
                Stmt* else_body_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* cond_;
                Stmt* if_;
                Stmt* else_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_IF_STMT_HH */
