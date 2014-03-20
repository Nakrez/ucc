#ifndef UCC_AST_ARRAY_TYPE_HH
# define UCC_AST_ARRAY_TYPE_HH

# include <ast/type.hh>

namespace ucc
{
    namespace ast
    {
        class ArrayType : public Type
        {
            public:
                ArrayType(const ucc::parse::location& loc);
                virtual ~ArrayType();

                const Type* sub_type_get() const;
                Type* sub_type_get();

                virtual bool extends_type(Type *t);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            private:
                Type* sub_type_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ARRAY_TYPE_HH */
