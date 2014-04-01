#ifndef UCC_AST_CONTINUE_STMT_HH
# define UCC_AST_CONTINUE_STMT_HH

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class ContinueStmt : public Stmt
        {
            public:
                ContinueStmt(const ucc::parse::location& loc);
                virtual ~ContinueStmt();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_CONTINUE_STMT_HH */
