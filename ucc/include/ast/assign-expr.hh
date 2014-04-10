#ifndef UCC_AST_ASSIGN_EXPR_HH
# define UCC_AST_ASSIGN_EXPR_HH

# include <string>

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class AssignExpr : public Expr
        {
            public:
                enum AssignOp
                {
                    ASSIGN,
                    MUL_ASSIGN,
                    DIV_ASSIGN,
                    MOD_ASSIGN,
                    PLUS_ASSIGN,
                    MINUS_ASSIGN,
                    LSHIFT_ASSIGN,
                    RSHIFT_ASSIGN,
                    BAND_ASSIGN,
                    BXOR_ASSIGN,
                    BOR_ASSIGN
                };

            public:
                AssignExpr(const ucc::parse::location& loc,
                           Expr* lvalue,
                           AssignOp op,
                           Expr* rvalue);
                virtual ~AssignExpr();

                const Expr* lvalue_get() const;
                Expr* lvalue_get();

                const Expr* rvalue_get() const;
                Expr* rvalue_get();

                AssignOp op_get() const;

                std::string op_to_str() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* lvalue_;
                Expr* rvalue_;
                AssignOp op_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ASSIGN_EXPR_HH */
