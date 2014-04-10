#ifndef UCC_AST_SWITCH_STMT_HH
# define UCC_AST_SWITCH_STMT_HH

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class SwitchStmt : public Stmt
        {
            public:
                SwitchStmt(const ucc::parse::location& loc,
                           Expr* cond,
                           Stmt* body);
                virtual ~SwitchStmt();

                const Expr* cond_get() const;
                Expr* cond_get();

                const Stmt* body_get() const;
                Stmt* body_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* cond_;
                Stmt* body_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_SWITCH_STMT_HH */
