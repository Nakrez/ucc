#ifndef UCC_AST_GOTO_STMT_HH
# define UCC_AST_GOTO_STMT_HH

# include <misc/symbol.hh>

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class GotoStmt : public Stmt
        {
            public:
                GotoStmt(const ucc::parse::location& loc,
                         const ucc::misc::Symbol& name);
                virtual ~GotoStmt();

                const ucc::misc::Symbol& name_get() const;
                ucc::misc::Symbol& name_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                ucc::misc::Symbol name_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_GOTO_STMT_HH */
