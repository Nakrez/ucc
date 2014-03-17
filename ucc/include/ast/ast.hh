#ifndef UCC_AST_AST_HH
# define UCC_AST_AST_HH

# include <location.hh>

# include <ast/visitor.hh>

namespace ucc
{
    namespace ast
    {
        class Ast
        {
            public:
                Ast(const ucc::parse::location& loc);
                virtual ~Ast();

                const ucc::parse::location& location_get() const;
                ucc::parse::location& location_get();

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;

            private:
                ucc::parse::location loc_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_AST_HH */
