#ifndef UCC_AST_OP_EXPR_HH
# define UCC_AST_OP_EXPR_HH

# include <string>

# include <ast/expr.hh>

namespace ucc
{
    namespace ast
    {
        class OpExpr : public Expr
        {
            public:
                enum Op
                {
                    OP_PLUS,
                    OP_MINUS,
                    OP_MUL,
                    OP_DIV,
                    OP_MOD,
                    OP_LSHIFT,
                    OP_RSHIFT,
                    OP_GT,
                    OP_GE,
                    OP_LT,
                    OP_LE,
                    OP_EQ,
                    OP_DIFF,
                    OP_BAND,
                    OP_XOR,
                    OP_BOR,
                    OP_AND,
                    OP_OR,
                    OP_COMA
                };

            public:
                OpExpr(const ucc::parse::location& loc,
                       Expr* lexpr,
                       Op op,
                       Expr* rexpr);
                virtual ~OpExpr();

                const Expr* lexpr_get() const;
                Expr* lexpr_get();

                const Expr* rexpr_get() const;
                Expr* rexpr_get();

                Op op_get() const;

                std::string op_to_str() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Expr* lexpr_;
                Expr* rexpr_;
                Op op_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_OP_EXPR_HH */
