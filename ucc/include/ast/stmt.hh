#ifndef UCC_AST_STMT_HH
# define UCC_AST_STMT_HH

# include <ast/ast.hh>

namespace ucc
{
    namespace ast
    {
        class Stmt : public Ast
        {
            public:
                Stmt(const ucc::parse::location& loc);
                virtual ~Stmt();

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_STMT_HH */
