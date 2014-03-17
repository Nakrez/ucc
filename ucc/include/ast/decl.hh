#ifndef UCC_AST_DECL_HH
# define UCC_AST_DECL_HH

# include <ast/ast.hh>

namespace ucc
{
    namespace ast
    {
        class Decl : public Ast
        {
            public:
                Decl(const ucc::parse::location& loc);
                virtual ~Decl();

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DECL_HH */
