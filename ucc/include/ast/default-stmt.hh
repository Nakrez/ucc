#ifndef UCC_AST_DEFAULT_STMT_HH
# define UCC_AST_DEFAULT_STMT_HH

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class DefaultStmt : public Stmt
        {
            public:
                DefaultStmt(const ucc::parse::location& loc, Stmt* body);
                virtual ~DefaultStmt();

                const Stmt* body_get() const;
                Stmt* body_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Stmt* body_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DEFAULT_STMT_HH */
