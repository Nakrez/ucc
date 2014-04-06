#ifndef UCC_AST_FOR_STMT_HH
# define UCC_AST_FOR_STMT_HH

# include <ast/stmt.hh>
# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class ForStmt : public Stmt
        {
            public:
                ForStmt(const ucc::parse::location& loc,
                        Expr* init,
                        Expr* cond,
                        Expr* inc,
                        Stmt* body);
                virtual ~ForStmt();

                const Expr* init_get() const;
                Expr* init_get();

                const Expr* cond_get() const;
                Expr* cond_get();

                const Expr* inc_get() const;
                Expr* inc_get();

                const Stmt* body_get() const;
                Stmt* body_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* init_;
                Expr* cond_;
                Expr* inc_;
                Stmt* body_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FOR_STMT_HH */
