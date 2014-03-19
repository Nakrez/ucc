#ifndef UCC_AST_TYPE_HH
# define UCC_AST_TYPE_HH

# include <ast/ast.hh>

namespace ucc
{
    namespace ast
    {
        class Type: public Ast
        {
            public:
                Type(const ucc::parse::location& loc);
                virtual ~Type();

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_TYPE_HH */
