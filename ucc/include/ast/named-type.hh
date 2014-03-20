#ifndef UCC_AST_NAMED_TYPE_HH
# define UCC_AST_NAMED_TYPE_HH

# include <ast/type.hh>

# include <misc/symbol.hh>

namespace ucc
{
    namespace ast
    {
        class NamedType : public Type
        {
            public:
                NamedType(const ucc::parse::location& loc,
                          const ucc::misc::Symbol& name);
                virtual ~NamedType();

                const ucc::misc::Symbol& name_get() const;
                ucc::misc::Symbol& name_get();

                virtual bool extends_type(Type *t);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            private:
                ucc::misc::Symbol name_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_NAMED_TYPE_HH */
