#ifndef UCC_AST_STRING_EXPR_HH
# define UCC_AST_STRING_EXPR_HH

# include <string>

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class StringExpr : public Expr
        {
            public:
                StringExpr(const ucc::parse::location& loc, std::string* str);
                virtual ~StringExpr();

                std::string* str_get();
                const std::string* str_get() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                std::string* str_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_STRING_EXPR_HH */
