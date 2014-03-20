#ifndef UCC_AST_FUNCTION_TYPE_HH
# define UCC_AST_FUNCTION_TYPE_HH

# include <ast/type.hh>

namespace ucc
{
    namespace ast
    {
        class FunctionType : public Type
        {
            public:
                FunctionType(const ucc::parse::location& loc);
                virtual ~FunctionType();

                const Type* return_type_get() const;
                Type* return_type_get();

                void return_type_set(Type* t);

                virtual bool extends_type(Type *t);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            private:
                Type* return_type_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FUNCTION_TYPE_HH */
