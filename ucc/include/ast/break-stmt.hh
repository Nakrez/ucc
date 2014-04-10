#ifndef UCC_AST_BREAK_STMT_HH
# define UCC_AST_BREAK_STMT_HH

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class BreakStmt : public Stmt
        {
            public:
                BreakStmt(const ucc::parse::location& loc);
                virtual ~BreakStmt();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_BREAK_STMT_HH */
