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

                bool is_const() const;
                bool is_volatile() const;
                bool is_unsigned() const;

                void const_set(bool b = true);
                void volatile_set(bool b = true);
                void unsigned_set(bool b = true);

                virtual bool extends_type(Type *t) = 0;

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;

            private:
                bool is_const_;
                bool is_volatile_;
                bool is_unsigned_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_TYPE_HH */
