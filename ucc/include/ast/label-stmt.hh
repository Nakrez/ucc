#ifndef UCC_AST_LABEL_STMT_HH
# define UCC_AST_LABEL_STMT_HH

# include <misc/symbol.hh>

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class LabelStmt : public Stmt
        {
            public:
                LabelStmt(const ucc::parse::location& loc,
                          const ucc::misc::Symbol& sym,
                          Stmt* stmt);
                virtual ~LabelStmt();

                const ucc::misc::Symbol& name_get() const;
                ucc::misc::Symbol& name_get();

                const Stmt* stmt_get() const;
                Stmt* stmt_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                ucc::misc::Symbol name_;
                Stmt* stmt_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_LABEL_STMT_HH */
