#ifndef UCC_AST_COMPOUND_STMT_HH
# define UCC_AST_COMPOUND_STMT_HH

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class CompoundStmt : public Stmt
        {
            public:
                CompoundStmt(const ucc::parse::location& loc,
                             AstList* compound);
                virtual ~CompoundStmt();

                const AstList* compound_get() const;
                AstList* compound_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                AstList* compound_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_COMPOUND_STMT_HH */
