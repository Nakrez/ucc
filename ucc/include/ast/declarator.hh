#ifndef UCC_AST_DECLARATOR_HH
# define UCC_AST_DECLARATOR_HH

# include <misc/symbol.hh>

# include <ast/decl.hh>

namespace ucc
{
    namespace ast
    {
        class Declarator : public Decl
        {
            public:
                Declarator(const ucc::parse::location& loc,
                           const ucc::misc::Symbol& s);
                virtual ~Declarator();

                const ucc::misc::Symbol& identifier_get() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            private:
                ucc::misc::Symbol identifier_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DECLARATOR_HH */
