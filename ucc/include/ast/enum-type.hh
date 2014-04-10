#ifndef UCC_AST_ENUM_TYPE_HH
# define UCC_AST_ENUM_TYPE_HH

# include <misc/symbol.hh>

# include <ast/enum-decl.hh>
# include <ast/type.hh>

namespace ucc
{
    namespace ast
    {
        class EnumType : public Type
        {
            public:
                EnumType(const ucc::parse::location& loc,
                         const ucc::misc::Symbol& name);
                virtual ~EnumType();

                const ucc::misc::Symbol& name_get() const;
                ucc::misc::Symbol& name_get();

                const EnumDecl* def_get() const;
                EnumDecl* def_get();

                void def_set(EnumDecl* def);

                virtual bool extends_type(Type*)
                {
                    return false;
                }

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                ucc::misc::Symbol name_;
                EnumDecl* def_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ENUM_TYPE_HH */
