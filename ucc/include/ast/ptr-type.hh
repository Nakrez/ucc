#ifndef UCC_AST_PTR_TYPE_HH
# define UCC_AST_PTR_TYPE_HH

# include <ast/type.hh>

namespace ucc
{
    namespace ast
    {
        class PtrType : public Type
        {
            public:
                PtrType(const ucc::parse::location& loc);
                PtrType(const ucc::parse::location& loc, Type* pointed_type);
                virtual ~PtrType();

                const Type* pointed_type_get() const;
                Type* pointed_type_get();

                virtual bool extends_type(Type *t);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Type* pointed_type_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_PTR_TYPE_HH */
