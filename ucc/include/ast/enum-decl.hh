#ifndef UCC_AST_ENUM_DECL_HH
# define UCC_AST_ENUM_DECL_HH

# include <ast/fwd.hh>

# include <ast/decl.hh>

namespace ucc
{
    namespace ast
    {
        class EnumDecl : public Decl
        {
            public:
                EnumDecl(const ucc::parse::location& loc,
                         const ucc::misc::Symbol& name,
                         EnumExprList* body);
                virtual ~EnumDecl();

                const EnumExprList* body_get() const;
                EnumExprList* body_get();

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                EnumExprList* body_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ENUM_DECL_HH */
