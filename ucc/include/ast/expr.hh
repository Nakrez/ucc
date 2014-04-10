#ifndef UCC_AST_EXPR_HH
# define UCC_AST_EXPR_HH

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class Expr : public Stmt
        {
            public:
                Expr(const ucc::parse::location& loc);
                virtual ~Expr();

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_EXPR_HH */
