#ifndef UCC_AST_DECL_HH
# define UCC_AST_DECL_HH

# include <misc/symbol.hh>

# include <ast/ast.hh>

namespace ucc
{
    namespace ast
    {
        class Decl : public Ast
        {
            public:
                Decl(const ucc::parse::location& loc,
                     const ucc::misc::Symbol& name);
                virtual ~Decl();

                const ucc::misc::Symbol& name_get() const;
                ucc::misc::Symbol& name_get();

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;

            protected:
                ucc::misc::Symbol name_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DECL_HH */
