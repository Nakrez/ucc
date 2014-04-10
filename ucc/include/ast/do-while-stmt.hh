#ifndef UCC_AST_DO_WHILE_STMT_HH
# define UCC_AST_DO_WHILE_STMT_HH

# include <ast/while-stmt.hh>

namespace ucc
{
    namespace ast
    {
        class DoWhileStmt : public WhileStmt
        {
            public:
                DoWhileStmt(const ucc::parse::location& loc,
                            Expr* cond,
                            Ast* body);
                virtual ~DoWhileStmt();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DO_WHILE_STMT_HH */
