#ifndef UCC_AST_WHILE_STMT_HH
# define UCC_AST_WHILE_STMT_HH

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class WhileStmt : public Stmt
        {
            public:
                WhileStmt(const ucc::parse::location& loc,
                          Expr* cond,
                          Ast* body);
                virtual ~WhileStmt();

                const Expr* cond_get() const;
                Expr* cond_get();

                const Ast* body_get() const;
                Ast* body_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* cond_;
                Ast* body_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_WHILE_STMT_HH */
